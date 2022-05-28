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

#include "Game/Components/PlayfieldComponent.hpp"
#include "Game/Playfield.hpp"
#include <cassert>

namespace OpenLabora
{

using TileInfo = tile::TileInfo;
using PlotType = plot::Type;

PlayfieldComponent::PlayfieldComponent(const sf::Vector2f& position,
                                       IResourceManager::Ptr resource_mgr)
{
    const auto plot_width = plot::kPlotWidthTileCount.Get(PlotType::Coastal);
    const auto offset = sf::Vector2f{ plot_width * tile::kTileWidth,
                                      kInitialPlotOffsetY };

    auto init_pos = position + offset;
    auto plot_top = plot::createCentralInitial(init_pos, resource_mgr);

    init_pos.y += tile::kTileHeight;
    auto plot_bottom = plot::createCentralInitial(init_pos, resource_mgr, true);

    auto pos_component = ecs::getComponent<PositionComponent>(plot_top);
    pos_component.position = init_pos;

    init_pos.y += tile::kTileHeight;
    pos_component = ecs::getComponent<PositionComponent>(plot_bottom);
    pos_component.position = init_pos;

    AddPlotToBottom(std::move(plot_top));
    AddPlotToBottom(std::move(plot_bottom));
}

void PlayfieldComponent::AddPlotToTop(const Plot& plot)
{
    const auto component = ecs::getComponent<PlotComponent>(plot);
    mPlots[component.GetType()].push_front(plot);
}

void PlayfieldComponent::AddPlotToBottom(const Plot& plot)
{
    const auto component = ecs::getComponent<PlotComponent>(plot);
    mPlots[component.GetType()].push_back(plot);
}

void PlayfieldComponent::AddPlotToTop(Plot&& plot)
{
    const auto component = ecs::getComponent<PlotComponent>(plot);
    mPlots[component.GetType()].emplace_front(std::move(plot));
}

void PlayfieldComponent::AddPlotToBottom(Plot&& plot)
{
    const auto component = ecs::getComponent<PlotComponent>(plot);
    mPlots[component.GetType()].emplace_back(std::move(plot));
}

bool PlayfieldComponent::IsPlotsLimitReached(plot::Type type) const
{
    assert(type >= plot::Type::Begin && type < plot::Type::End);
    auto&& plots = mPlots.Get(type);
    if (plots.empty()) {
        return false;
    }
    return plots.size() >= plot::kPlotMaxCount.Get(type);
}

} // namespace OpenLabora

#if 0 // TODO: Reimplement Build Mode
Plot::OptionalTileInfo
Playfield::GetTileInfoUnderPoint(const sf::Vector2f& point) const
{
    // This is just a general check, we cannot rely on it for weirdly shaped pfs
    if (!mObject.getGlobalBounds().contains(point)) {
        return std::nullopt;
    }

    auto local_pos = GetPosition() - point;

    auto type = PlotType::Begin;
    while (type != PlotType::End &&
           local_pos.x < Tile::kTileWidth * Plot::GetPlotWidthTileCount(type)) {
        local_pos.x -= Tile::kTileWidth;
        ++type;
    }

    auto&& plot_deq = mPlots.find(type);
    if (plot_deq == mPlots.end() || plot_deq->second.empty()) {
        return std::nullopt;
    }

    auto plot_top = plot_deq->second.front().GetPosition().y;
    auto plot_index = static_cast<int>((plot_top - point.y) / Tile::kTileHeight);

    if (plot_index < 0 || plot_index > plot_deq->second.size()) {
        return std::nullopt;
    }

    return plot_deq->second[plot_index].GetTileInfoUnderPoint(point);
}
#endif

#if 0 // TODO: Reimplement markers (again)
std::tuple<sf::Vector2f, sf::Vector2f>
PlayfieldComponent::GetExpansionMarkerPositions(PlotType type) const
{
    assert(type != PlotType::End);
    const auto&& plot_deq = mPlots.find(type);
    bool plots_exist = plot_deq != mPlots.end();

    // In the case where no plots of specified type exist the markers positions
    // depend on how much central plots exist. There are always 2+ central plots
    if (!plots_exist) {
        const auto&& central_deq = mPlots.find(PlotType::Central);
        assert(central_deq != mPlots.end());

        const auto top_left_pos = central_deq->second.front().GetPosition();
        const auto btm_left_pos = central_deq->second.back().GetPosition();

        auto pf_position = GetPosition();
        pf_position.x += Plot::GetOffsetXForPlotType(type);

        return {{pf_position.x, top_left_pos.y - Tile::kTileHeight},
                {pf_position.x, btm_left_pos.y}};
    }

    const auto top_left_pos = plot_deq->second.front().GetPosition();
    const auto btm_left_pos = plot_deq->second.back().GetPosition();

    const auto offset_tile_number = type == PlotType::Central ? 1 : 2;
    const auto offset_y  = Tile::kTileHeight * offset_tile_number;

    return {{top_left_pos.x, top_left_pos.y - offset_y},
            {btm_left_pos.x, btm_left_pos.y + Tile::kTileHeight}};
}

uint32_t Playfield::GetDisposableMarkerCount(Plot::PlotType plot_type) const
{
    assert(plot_type != PlotType::End);
    auto&& plot_deq = mPlots.find(plot_type);
    if (plot_deq != mPlots.end()) {
        return 0;
    }
    auto&& central_deq = mPlots.find(PlotType::Central);
    assert(central_deq != mPlots.end());
    return static_cast<uint32_t>(central_deq->second.size()) - 1;
}
#endif
