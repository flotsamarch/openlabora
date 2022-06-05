// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include "Game/Components/MarkerControllerComponent.hpp"
#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

void MarkerControllerComponent
::RemoveExcessMarkers(Playfield::PtrConst playfield)
{
    for (auto&& [plot_type, markers] : mMarkers) {
        if (markers.empty()) {
            continue;
        }

        auto&& pf_component = ecs::getComponent<PlayfieldComponent>(*playfield);

        if (pf_component.IsPlotsLimitReached(plot_type)) {
            mSelectedMarker = nullptr;
            mMarkers[plot_type].clear();
            continue;
        }

        if (!pf_component.GetPlots(plot_type).IsEmpty()) {
            mSelectedMarker = nullptr;
            auto pred = [] (auto&& marker)
            {
                using EMC = ExpansionMarkerComponent;
                auto&& component = ecs::getComponent<EMC>(*marker);
                return component.GetType() == marker::Type::Filling;
            };

            auto to_erase = std::remove_if(markers.begin(), markers.end(), pred);
            markers.erase(to_erase, markers.end());
        }
    }
}

std::shared_ptr<ExpansionMarker>
MarkerControllerComponent::CreateMarker(marker::Type marker_type,
                                        plot::Type plot_type,
                                        std::function<void()> on_left_released,
                                        IResourceManager::Ptr resource_mgr)
{
    // @return lambda that assigns provided marker to mSelectedMarker
    auto select_on_left_released = [&selected = mSelectedMarker]
    (std::weak_ptr<Marker> wmarker)
    {
        return [&selected, wmarker]
        {
            auto marker = wmarker.lock();
            selected = marker;
        };
    };

    auto marker = marker::create(marker_type, plot_type, resource_mgr);

    auto&& signals = ecs::getComponent<SignalComponent>(*marker);
    // Order is important! Marker should be selected before it is acted upon
    signals.Connect(signals::kOnSelect, select_on_left_released(marker));
    signals.Connect(signals::kOnSelect, on_left_released);

    return marker;
}

void MarkerControllerComponent::DeselectMarker()
{
    if (mSelectedMarker != nullptr) {
        using SignalCmpnt = SignalComponent;
        auto&& signal_cmpnt = ecs::getComponent<SignalCmpnt>(*mSelectedMarker);
        signal_cmpnt.Emit(signals::kOnDeselect);
        mSelectedMarker = nullptr;
    }
}

void MarkerControllerComponent
::CreateMissingMarkers(Playfield::PtrConst playfield,
                       std::function<void()> on_left_released_delegate,
                       IResourceManager::Ptr resource_mgr)
{
    for (auto&& [plot_type, markers] : mMarkers) {
        auto&& pf_component = ecs::getComponent<PlayfieldComponent>(*playfield);

        if (pf_component.IsPlotsLimitReached(plot_type)) {
            continue;
        }

        if (markers.empty()) {
            auto upper = CreateMarker(marker::Type::Upper,
                                      plot_type,
                                      on_left_released_delegate,
                                      resource_mgr);

            auto lower = CreateMarker(marker::Type::Lower,
                                      plot_type,
                                      on_left_released_delegate,
                                      resource_mgr);

            markers.push_back(upper);
            markers.push_back(lower);
        }

        if (auto plots = pf_component.GetPlots(plot_type); plots.IsEmpty()) {
            constexpr auto central = plot::Type::Central;
            const auto plot_count = pf_component.GetPlots(central).GetSize();
            while (markers.size() < plot_count + 1) {
                auto marker = CreateMarker(marker::Type::Filling,
                                           plot_type,
                                           on_left_released_delegate,
                                           resource_mgr);
                auto last_it = --markers.end();
                markers.insert(last_it, marker);
            }
        }
    }
}

void MarkerControllerComponent::TranslateMarkers(Playfield::PtrConst playfield)
{
    using RectAreaCmpnt = RectangleInteractionAreaComponent;
    using PositionCmpnt = PositionComponent;
    using SpriteCmpnt = SpriteComponent;
    using Rect = sf::RectangleShape;

    for (auto&& [plot_type, markers] : mMarkers) {
        if (markers.empty()) {
            continue;
        }

        auto&& pf_component = ecs::getComponent<PlayfieldComponent>(*playfield);
        auto plots = pf_component.GetPlots(plot_type);

        auto [upper_pos, lower_pos] =
                marker::GetBoundaryMarkerPositions(plot_type, playfield);

        auto&& upper_marker = *markers.front();
        auto&& lower_marker = *markers.back();

        auto&& upper_pos_cmpnt = ecs::getComponent<PositionCmpnt>(upper_marker);
        auto&& lower_pos_cmpnt = ecs::getComponent<PositionCmpnt>(lower_marker);
        upper_pos_cmpnt.position = upper_pos;
        lower_pos_cmpnt.position = lower_pos;

        auto&& upper_sprite = ecs::getComponent<SpriteCmpnt>(upper_marker);
        auto&& lower_sprite = ecs::getComponent<SpriteCmpnt>(lower_marker);
        upper_sprite.SetPosition(upper_pos);
        lower_sprite.SetPosition(lower_pos);

        auto&& upper_area_comp = ecs::getComponent<RectAreaCmpnt>(upper_marker);
        auto&& lower_area_comp = ecs::getComponent<RectAreaCmpnt>(lower_marker);
        upper_area_comp.SetOffset({ 0.f, 0.f });
        lower_area_comp.SetOffset({ 0.f, 0.f });

        const auto bounds = upper_sprite.GetLocalBounds();
        constexpr auto factor = marker::kMarkerOverlapFactor;
        constexpr auto factor_rev = (1 - marker::kMarkerOverlapFactor);
        const auto boundary_clickable_height = bounds.height * factor_rev;

        if (!plots.IsEmpty()) {
            const auto shape = Rect{{ bounds.width, bounds.height }};
            upper_area_comp.SetShape(shape);
            lower_area_comp.SetShape(shape);
        } else {
            const auto shape = Rect{{ bounds.width, boundary_clickable_height }};
            upper_area_comp.SetShape(shape);
            lower_area_comp.SetShape(shape);
            lower_area_comp.SetOffset({ 0.f, factor * bounds.height });
        }

        plots = pf_component.GetPlots(plot::Type::Central);

        const auto overlap_space = bounds.height * factor * 2;
        const auto upper_marker_bottom_edge = upper_pos.y + bounds.height;
        const auto gap_between_markers = lower_pos.y - upper_marker_bottom_edge;
        const auto total_available_space = gap_between_markers + overlap_space;
        const auto rect_height = total_available_space / (plots.GetSize() - 1);
        const auto interaction_rect = Rect{{ bounds.width, rect_height }};

        const auto offset_y = boundary_clickable_height - tile::kTileHeight;
        const auto offset_delta = rect_height - tile::kTileHeight;
        auto offset = sf::Vector2f{ 0.f , offset_y };

        auto update = [pos = upper_pos, &offset, interaction_rect, offset_delta]
        (auto&& marker) mutable
        {
            pos.y += tile::kTileHeight;
            auto&& area_cmpnt = ecs::getComponent<RectAreaCmpnt>(*marker);
            area_cmpnt.SetOffset(offset);
            area_cmpnt.SetShape(interaction_rect);

            auto&& position_cmpnt = ecs::getComponent<PositionCmpnt>(*marker);
            position_cmpnt.position = pos;

            auto&& sprite_cmpnt = ecs::getComponent<SpriteComponent>(*marker);
            sprite_cmpnt.SetPosition(pos);

            offset.y += offset_delta;
        };

        auto end = std::next(markers.rbegin());
        std::for_each(std::next(markers.begin()), end.base(), update);
    }
}

bool MarkerControllerComponent
::ForwardEventToMarkers(const sf::Vector2f& mouse_world_pos,
                        const sf::Event& event) const
{
    for (auto&& [plot_type, markers] : mMarkers) {
        auto func = [&mouse_world_pos, &event] (auto&& marker)
        { return marker::handleEvent(marker, mouse_world_pos, event); };
        if (std::any_of(markers.begin(), markers.end(), func)) {
            return true;
        }
    }
    return false;
}

} // namespace OpenLabora
