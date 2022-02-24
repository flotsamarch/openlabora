#include <ranges>
#include "game/MarkerManager.hpp"
#include "resource/IResourceManager.hpp"
#include "GUI/Utility.hpp"


namespace OpenLabora
{

MarkerManager::MarkerManager(GameController::Ptr ctlr,
                             IResourceManager& res_mgr,
                             sfg::Window::Ptr central_confirm_window,
                             sfg::Button::Ptr central_confirm_button,
                             sfg::Window::Ptr side_confirm_window,
                             sfg::Button::Ptr side_confirm_button)
    : mController{ ctlr }, mCentralConfirmWindow{ central_confirm_window },
      mCentralConfirmButton{ central_confirm_button },
      mSideConfirmWindow{ side_confirm_window },
      mSideConfirmButton{ side_confirm_button }
{
    auto coastal_plot = Plot{ Plot::kCostalPlot, res_mgr };
    mPlotsForMarkerCreation.insert({PlotType::Coastal, coastal_plot});
    mPlotsForMarkerCreation.insert({PlotType::Coastal, coastal_plot});

    auto central_plot_top = Plot{ Plot::kCentralPlotTop, res_mgr };
    auto central_plot_bottom = Plot{ Plot::kCentralPlotBottom, res_mgr };
    mPlotsForMarkerCreation.insert({PlotType::Central, central_plot_top});
    mPlotsForMarkerCreation.insert({PlotType::Central, central_plot_bottom});

    auto mountain_plot_top = Plot{ Plot::kMountainPlotTop, res_mgr };
    auto mountain_plot_bottom = Plot{ Plot::kMountainPlotBottom, res_mgr };
    mPlotsForMarkerCreation.insert({PlotType::Mountain, mountain_plot_top});
    mPlotsForMarkerCreation.insert({PlotType::Mountain, mountain_plot_bottom});

    for (auto type = PlotType::Begin, end = PlotType::End; type < end; ++type) {
        CreateMarker(type, MarkerType::Upper);
        CreateMarker(type, MarkerType::Lower);
        if (type != PlotType::Central) {
            CreateMarker(type, MarkerType::Disposable);
        }
    }

    UpdateMarkers();
}

MarkerManager::~MarkerManager()
{
    for (auto&& [plot_type, arr] : mMarkers) {
        for (auto&& marker : arr) {
            mController->RemoveMarker(marker);
        }
        arr.clear();
    }
    auto&& side_signal = mSideConfirmButton->GetSignal(Widget::OnMouseLeftRelease);
    auto&& central_signal =
        mCentralConfirmButton->GetSignal(Widget::OnMouseLeftRelease);

    side_signal.Disconnect(mCentralUpdateSignalId);
    central_signal.Disconnect(mCentralUpdateSignalId);
}

void MarkerManager::UpdateMarkers()
{
    auto playfield = mController->GetActivePlayerPlayfield();

    for (auto&& [plot_type, arr] : mMarkers) {
        const auto disp_count = playfield->GetDisposableMarkerCount(plot_type);
        if (disp_count == 0) {
            auto [first, last] = std::ranges::remove_if(arr,
            [ctlr = mController] (auto&& marker)
            {
                auto remove = marker->GetType() == MarkerType::Disposable;
                if (remove) {
                    ctlr->RemoveMarker(marker);
                }
                return remove;
            });
            arr.erase(first, last);
        } else {
            while (disp_count > arr.size() - 2) {
                CreateMarker(plot_type, MarkerType::Disposable);
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

            if (upper != nullptr && lower != nullptr) {
                const auto [top_marker_pos, btm_marker_pos] =
                    playfield->GetExpansionMarkerPositions(plot_type);
                upper->SetPosition(top_marker_pos);
                lower->SetPosition(btm_marker_pos);
            }

            auto position = upper->GetPosition();
            std::for_each(arr.begin() + 2, arr.end(), [&position] (auto&& marker)
            {
                position.y += Tile::kTileHeight;
                marker->SetPosition(position);
            });
        }
    }
}

void MarkerManager::CreateMarker(PlotType plot_type, MarkerType marker_type)
{
    assert(marker_type != MarkerType::End);
    assert(plot_type != PlotType::End);

    auto type_index = static_cast<size_t>(marker_type);
    if (type_index < 2) { // Meaning either Upper or Lower marker type
        assert(mMarkers[plot_type].size() == type_index);
    }

    bool is_central = plot_type == PlotType::Central;
    auto window = is_central ? mCentralConfirmWindow : mSideConfirmWindow;
    auto button = is_central ? mCentralConfirmButton : mSideConfirmButton;

    auto&& plot = mPlotsForMarkerCreation.find(plot_type);
    assert(plot != mPlotsForMarkerCreation.end());


    if (is_central) {
        auto marker = mController->CreateMarker(mController,
                                                window,
                                                button,
                                                marker_type,
                                                plot->second);
        mMarkers[plot_type].push_back(marker);
    } else {
        auto marker = mController->CreateMarker(mController,
                                                window,
                                                button,
                                                marker_type,
                                                plot->second,
                                                (++plot)->second);
        mMarkers[plot_type].push_back(marker);
    }
    auto update_markers = [manager = this] { manager->UpdateMarkers(); };
    // Reconnect signal to ensure correct order of calls
    auto&& signal_id = is_central ? mCentralUpdateSignalId : mSideUpdateSignalId;
    button->GetSignal(Widget::OnMouseLeftRelease).Disconnect(signal_id);
    signal_id = connect(button, Widget::OnMouseLeftRelease, update_markers);
}


} // namespace OpenLabora