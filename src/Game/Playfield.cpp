#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cmath>
#include "Game/Playfield.hpp"
#include "Resource/ResourceManager.hpp"

namespace OpenLabora
{

namespace
{
using TileInfo = Tile::TileInfo;
using PlotType = Plot::PlotType;
using MarkerType = ExpansionMarker::MarkerType;
}

Playfield::Playfield(IResourceManager::Ptr res_mgr)
    : mResMgr{ res_mgr }
{
    auto plot_top = Plot{ Plot::kCentralPlot, res_mgr };
    auto plot_bottom = Plot{ Plot::kCentralPlotAlt, res_mgr };
    auto offset_x = Tile::kTileWidth *
        Plot::GetPlotWidthTileCount(PlotType::Coastal);
    auto init_pos =
        sf::Vector2f{ static_cast<float>(offset_x), kInitialPlotOffset };
    init_pos += mObject.getPosition();
    plot_top.SetPosition(init_pos);
    plot_bottom.SetPosition(init_pos.x, init_pos.y + Tile::kTileHeight);
    AddPlotToBottom(plot_top);
    AddPlotToBottom(plot_bottom);

    mGroundTexture.create(Tile::kTileWidth * kMaxFieldWidth,
                          Tile::kTileHeight * kMaxFieldHeight);
    mObject.setTexture(mGroundTexture.getTexture(), true);
    DrawPlotsAsSprite();
}

void Playfield::DrawPlotsAsSprite()
{
    mGroundTexture.clear();
    for (auto&& sub_plots : mPlots) {
        for (auto&& item : sub_plots.second) {
            mGroundTexture.draw(item.GetDrawableObject());
        }
    }
    mGroundTexture.display();
    mObject.setTexture(mGroundTexture.getTexture(), true);
}

TileInfo Playfield::GetTileInfoUnderPoint(const sf::Vector2f& point) const
{
    // This is just a general check, we cannot rely on it for weirdly shaped pfs
    if (!mObject.getGlobalBounds().contains(point)) {
        return Tile::kBadTile;
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
        return Tile::kBadTile;
    }

    auto plot_top = plot_deq->second.front().GetPosition().y;
    auto plot_index = static_cast<int>((plot_top - point.y) / Tile::kTileHeight);

    if (plot_index < 0 || plot_index > plot_deq->second.size()) {
        return Tile::kBadTile;
    }

    return plot_deq->second[plot_index].GetTileInfoUnderPoint(point);
}

std::tuple<sf::Vector2f, sf::Vector2f>
Playfield::GetExpansionMarkerPositions(PlotType type) const
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

bool Playfield::IsPlotsLimitReached(PlotType plot_type) const
{
    assert(plot_type != PlotType::End);
    const auto&& plot_deq = mPlots.find(plot_type);
    if (plot_deq == mPlots.end()) {
        return false;
    }

    const auto&& count = kMaxPlotCount.find(plot_type);
    assert(count != kMaxPlotCount.end());
    return count->second <= plot_deq->second.size();
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

void Playfield::SetPosition(const sf::Vector2f& position)
{
    auto delta_pos = position - GetPosition();
    mObject.setPosition(position);
    auto width = static_cast<float>(mGroundTexture.getSize().x);
    auto height = static_cast<float>(mGroundTexture.getSize().y);
    auto view = sf::View({position.x, position.y,
                          width, height});
    mGroundTexture.setView(view);
    for (auto&& plot_deq : mPlots) {
        for (auto&& plot : plot_deq.second) {
            plot.Move(delta_pos);
        }
    }
    DrawPlotsAsSprite();
}

void Playfield::SetPosition(float offset_x, float offset_y)
{
    SetPosition({offset_x, offset_y});
}

void Playfield::AddPlotToTop(const Plot& plot)
{
    mPlots[plot.GetType()].push_front(plot);
    DrawPlotsAsSprite();
}

void Playfield::AddPlotToBottom(const Plot& plot)
{
    mPlots[plot.GetType()].push_back(plot);
    DrawPlotsAsSprite();
}

} // namespace OpenLabora
