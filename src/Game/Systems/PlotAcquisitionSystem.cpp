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

#include <cassert>
#include "ECS/Entity.hpp"
#include "Game/Systems/PlotAcquisitionSystem.hpp"
#include "Game/Components/LotDequeComponent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"
#include "Game/PlotAcquisitionMarker.hpp"
#include "ECS/MassAssignComponents.hpp"
#include "Game/Plot.hpp"

namespace open_labora
{

namespace marker = plot_acquisition_marker;

using MarkerContainer = PlotAcquisitionSystem::MarkerContainer;
using LotsInfoMap = lot_deque::LotsInfoMap;
using LotsInfo = lot_deque::LotsInfo;

PlotAcquisitionSystem::PlotAcquisitionSystem(Registry&,
                                             IResourceManager::Ptr resource_mgr)
    : mResourceMgr{ resource_mgr }
{
}

namespace plot_acquisition
{

void removeExcessMarkers(MarkerContainer& markers,
                         lot::Type type,
                         const LotsInfoMap& lots_info,
                         RegistryRef registry)
{
    assert(lots_info.find(type) != lots_info.end());

    auto destroy_marker = [registry] (auto&& marker) mutable
    {
        registry.DestroyEntity(marker);
    };

    auto count = lots_info.find(type)->second.count;
    if (count >= lot::getMaximumCount(type)) {
        std::for_each(markers.begin(), markers.end(), destroy_marker);
        markers.clear();
        return;
    }

    if (markers.size() > 2 && count > 0) {
        auto begin = std::next(markers.begin(), 2);
        auto end = markers.end();
        std::for_each(begin, end, destroy_marker);
        markers.erase(begin, end);
    }
}

void createMissingMarkers(MarkerContainer& markers,
                          lot::Type type,
                          const LotsInfoMap& lots_info,
                          RegistryRef registry,
                          IResourceManager::Ptr resource_mgr)
{
    auto create_marker = [registry, resource_mgr] (lot::Type type,
                                                   bool does_add_to_top)
    {
        return marker::create(registry, type, does_add_to_top, resource_mgr);
    };

    assert(lots_info.find(type) != lots_info.end());
    auto info = lots_info.find(type)->second;

    if (info.count >= lot::getMaximumCount(type)) {
        return;
    }

    const auto anchor_type = getAnchorLotType(type);
    assert(lots_info.find(anchor_type) != lots_info.end());
    const auto anchor_info = lots_info.find(anchor_type)->second;
    if (anchor_info.count == 0 && info.count == 0) {
        return;
    }

    if (markers.empty()) {
        markers.push_back(create_marker(type, true));
    }

    const auto anchor_lot_count = anchor_info.count;
    const auto extra_marker_count = plot::getLotCount(type) - 1;
    const auto marker_count_no_lots = anchor_lot_count + extra_marker_count;
    const auto total_count = info.count > 0 ? 2 : marker_count_no_lots;

    while (markers.size() < total_count) {
        markers.push_back(create_marker(type, false));
    }

    assert(markers.size() >= 2);
}

void updateMarkerPositions(MarkerContainer& markers,
                           lot::Type type,
                           const LotsInfoMap& lots_info)
{
    if (markers.empty()) {
        return;
    }

    const auto anchor_info_it = lots_info.find(getAnchorLotType(type));
    const auto this_info_it = lots_info.find(type);
    assert(anchor_info_it != lots_info.end());
    assert(this_info_it != lots_info.end());

    constexpr auto tile_h = tile::kTileHeight;
    const auto plot_lots_count = plot::getLotCount(type);

    auto info = this_info_it->second;
    if (info.count == 0) {
        const auto position_x = lot::getOffsetX(type);
        auto position_y = anchor_info_it->second.position.y;
        position_y -= (plot_lots_count - 1) * tile_h;
        info.position = Vector2f{ position_x, position_y };
    }

    const auto last_marker_y = info.position.y + info.count * tile_h;
    const auto position_x = info.position.x;

    if (info.count > 0) {
        const auto position_y = info.position.y - plot_lots_count * tile_h;
        marker::setPosition(markers.front(), { position_x, position_y });
        marker::setPosition(markers.back(), { position_x, last_marker_y });
        return;
    }

    std::for_each(markers.begin(), markers.end(), [&info] (auto&& marker) mutable
    {
        marker::setPosition(marker, { info.position.x, info.position.y });
        info.position.y += tile_h;
    });
}

void updateMarkerInteractionAreas(MarkerContainer& markers)
{
    if (markers.empty()) {
        return;
    }

    assert(markers.size() >= 2);
    constexpr auto factor = marker::kMarkerOverlapFactor;
    constexpr auto factor_inverse = (1 - factor);
    constexpr auto tile_h = tile::kTileHeight;

    auto first_marker = markers.front();
    auto last_marker = markers.back();

    const auto marker_count = markers.size();
    const auto sprite = first_marker.GetComponent<SpriteComponent>();
    const auto bounds = sprite.GetLocalBounds();
    const auto outer_marker_clickarea_h = bounds.height * factor_inverse;
    const auto zero_v2f = Vector2f{ 0.f, 0.f };

    const auto first_marker_y = first_marker.GetComponent<PositionComponent>().y;
    const auto last_marker_y = last_marker.GetComponent<PositionComponent>().y;

    if (marker_count == 2) {
        const auto size = sf::Vector2f{ bounds.width, bounds.height };
        marker::setInteractiveRect(first_marker, zero_v2f, size);
        marker::setInteractiveRect(last_marker, zero_v2f, size);
    } else {
        const auto size = Vector2f{ bounds.width, outer_marker_clickarea_h };
        const auto last_offset = Vector2f{ 0.f, factor * bounds.height };
        marker::setInteractiveRect(first_marker, zero_v2f, size);
        marker::setInteractiveRect(last_marker, last_offset, size);
    }

    const auto overlap_space = bounds.height * factor * 2;
    const auto first_marker_bottom_y = first_marker_y + bounds.height;
    const auto inner_container_h = last_marker_y - first_marker_bottom_y;
    const auto total_available_space = inner_container_h + overlap_space;
    const auto rect_height = total_available_space / (marker_count - 2);
    const auto rect_size = sf::Vector2f{ bounds.width, rect_height };
    const auto clickarea_offset_y = outer_marker_clickarea_h - tile_h;
    const auto clickarea_offset_y_delta = rect_height - tile_h;

    auto clickarea_offset = Vector2f{ 0.f, clickarea_offset_y};
    std::for_each(std::next(markers.begin()),
                  std::prev(markers.end()),
    [rect_size, &clickarea_offset_y_delta, &clickarea_offset]
    (Entity marker)
    {
        marker::setInteractiveRect(marker, clickarea_offset, rect_size);
        clickarea_offset.y += clickarea_offset_y_delta;
    });
}

} // namespace plot_acquisition

namespace system = plot_acquisition;

void systemHandleEvent(PlotAcquisitionSystem& system,
                       RegistryRef registry,
                       const UpdateMarkersEvent&)
{
    auto lots_info = lot_deque::createLotsInfo(registry);
    auto&& map = system.GetMarkerMap();

    for (auto&& [type, markers] : map) {
        system::removeExcessMarkers(markers, type, lots_info, registry);

        system::createMissingMarkers(markers,
                                     type,
                                     lots_info,
                                     registry,
                                     system.GetResourceManager());

        system::updateMarkerPositions(markers, type, lots_info);

        system::updateMarkerInteractionAreas(markers);
    }
}

} // namespace open_labora
