#include <ranges>
#include <GameState/Controllers/GameController.hpp>
#include "game/MarkerManager.hpp"
#include "Resource/IResourceManager.hpp"


namespace OpenLabora
{

MarkerManager::MarkerManager(GameController::Ptr controller)
    : mController{ controller }
{
    auto res_manager = controller->GetResourceManager();
    // In case plot_type != PT::Central number of items in this map tells
    // if there are 2 or 1 plots in marker
    auto coastal_plot = Plot{ Plot::kCostalPlot, res_manager };
    mPlotsForMarkerCreation.insert({PlotType::Coastal, coastal_plot});
    mPlotsForMarkerCreation.insert({PlotType::Coastal, coastal_plot});

    auto central_plot = Plot{ Plot::kCentralPlot, res_manager };
    auto central_plot_alt = Plot{ Plot::kCentralPlotAlt, res_manager };
    mPlotsForMarkerCreation.insert({PlotType::Central, central_plot});
    mPlotsForMarkerCreation.insert({PlotType::Central, central_plot_alt});

    auto mountain_plot_bottom = Plot{ Plot::kMountainPlotBottom, res_manager };
    auto mountain_plot_top = Plot{ Plot::kMountainPlotTop, res_manager };
    mPlotsForMarkerCreation.insert({PlotType::Mountain, mountain_plot_bottom});
    mPlotsForMarkerCreation.insert({PlotType::Mountain, mountain_plot_top});
}

MarkerManager::~MarkerManager()
{
    for (auto&& [plot_type, arr] : mMarkers) {
        for (auto&& marker : arr) {
            mController->RemoveMarker(marker);
        }
        arr.clear();
    }
}

void MarkerManager::UpdateMarkers(Delegate on_select)
{
    auto playfield = mController->GetActivePlayerPlayfield();

    if (mMarkers.empty()) {
        for (auto type = PlotType::Begin, end = PlotType::End; type < end; ++type) {
            CreateMarker(type, MarkerType::Upper, on_select);
            CreateMarker(type, MarkerType::Lower, on_select);
            if (type != PlotType::Central) {
                CreateMarker(type, MarkerType::Disposable, on_select);
            }
        }
    }

    for (auto&& [plot_type, arr] : mMarkers) {
        const auto disp_count = playfield->GetDisposableMarkerCount(plot_type);
        if (disp_count == 0) {
            auto last = std::remove_if(arr.begin(), arr.end(),
            [this] (auto&& marker)
            {
                auto remove = marker->GetType() == MarkerType::Disposable;
                if (remove) {
                    mController->RemoveMarker(marker);
                }
                return remove;
            });
            arr.erase(last, arr.end());
        } else {
            while (disp_count > arr.size() - 2) {
                CreateMarker(plot_type, MarkerType::Disposable, on_select);
            }
        }

        if (playfield->IsPlotsLimitReached(plot_type))
        {
            for (auto&& marker : arr) {
                if (marker != nullptr) {
                    mController->RemoveMarker(marker);
                    marker.reset();
                }
            }

            arr.clear();
        } else {
            auto upper = arr.at(static_cast<size_t>(MarkerType::Upper));
            auto lower = arr.at(static_cast<size_t>(MarkerType::Lower));
            assert(upper->GetType() == MarkerType::Upper);
            assert(lower->GetType() == MarkerType::Lower);

            const auto [top_marker_pos, btm_marker_pos] =
                playfield->GetExpansionMarkerPositions(plot_type);
            if (upper != nullptr && lower != nullptr) {
                upper->SetPosition(top_marker_pos);
                lower->SetPosition(btm_marker_pos);

                if (disp_count == 0) {
                    upper->ResetClickableArea();
                    lower->ResetClickableArea();
                }
            }

            const auto factor = (1 - ExpansionMarker::kMarkerOverlapFactor);
            const auto bounds = upper->GetLocalBounds();
            const auto available_space = btm_marker_pos.y - top_marker_pos.y;
            auto marker_size = sf::Vector2f{ bounds.width, available_space };
            // Same as marker_size.y - height * factor + heigth * (1 - factor)
            marker_size.y -= 2 * bounds.height * factor - bounds.height;
            marker_size.y /= disp_count;
            marker_size.x = bounds.width;

            const auto upper_clickable_height = bounds.height * factor;
            const auto delta = marker_size.y - Tile::kTileHeight;
            const auto offset_y = upper_clickable_height - Tile::kTileHeight;
            auto offset = sf::Vector2f{ 0.f, offset_y };
            auto position = upper->GetPosition();

            std::for_each(arr.begin() + 2, arr.end(),
            [&position, &offset, marker_size, delta] (auto&& marker)
            {
                position.y += Tile::kTileHeight;
                marker->SetClickableArea(offset, marker_size);
                marker->SetPosition(position);
                offset.y += delta;
            });
        }
    }
}

void MarkerManager::CreateMarker(PlotType plot_type,
                                 MarkerType marker_type,
                                 Delegate on_select)
{
    assert(marker_type != MarkerType::End);
    assert(plot_type != PlotType::End);

    auto type_index = static_cast<size_t>(marker_type);
    if (type_index < 2) { // Meaning either Upper or Lower marker type
        assert(mMarkers[plot_type].size() == type_index);
    }

    const bool is_central = plot_type == PlotType::Central;

    auto [plot, end] = mPlotsForMarkerCreation.equal_range(plot_type);
    assert(std::distance(plot, end) > 1);

    auto plot_alt = plot++;
    assert(plot != mPlotsForMarkerCreation.end());
    auto marker = mController->CreateMarker(marker_type,
                                            plot->second,
                                            plot_alt->second);
    assert(marker != nullptr);
    mMarkers[plot_type].push_back(marker);
    marker->SetSelectDelegate(on_select);
}

} // namespace OpenLabora
