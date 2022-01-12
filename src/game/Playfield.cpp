#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cmath>
#include "game/Playfield.hpp"
#include "resource/ResourceManager.hpp"

namespace
{

using TileInfo = Tile::TileInfo;
using PlotType = Plot::PlotType;

}

Playfield::Playfield(const IResourceManager& res_mgr)
    : mResMgr{ res_mgr }
{
    auto plot_top = Plot{ Plot::kCentralPlotTop, res_mgr };
    auto plot_bottom = Plot{ Plot::kCentralPlotBottom, res_mgr };
    auto offset_x = Tile::kTileWidth *
        Plot::GetPlotWidthTileCount(PlotType::Coastal);
    plot_top.SetPosition(offset_x, 0);
    plot_bottom.SetPosition(offset_x, Tile::kTileHeight);
    PushPlotBack(plot_top);
    PushPlotBack(plot_bottom);

    mGroundTexture.create(Tile::kTileWidth * kFieldWidth,
                          Tile::kTileHeight * kFieldHeight);
    DrawPlotsAsSprite();
}

void Playfield::DrawPlotsAsSprite()
{
    for (auto&& sub_plots : mPlots) {
            for (auto&& item : sub_plots.second) {
                auto&& plot_sprite = item.GetDrawableObject();
                mGroundTexture.draw(plot_sprite);
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
    auto plot_index = (plot_top - point.y) / Tile::kTileHeight;

    if (plot_index < 0 || plot_index > plot_deq->second.size()) {
        return Tile::kBadTile;
    }

    return plot_deq->second[plot_index].GetTileInfoUnderPoint(point);
}

std::tuple<float, float>
Playfield::GetLandTopAndBottomEdges(Plot::PlotType type) const
{
    auto&& plot_deq = mPlots.find(type);
    if (plot_deq == mPlots.end() || plot_deq->second.empty()) {
        return {0.f, 0.f};
    }

    return { plot_deq->second.front().GetPosition().y,
        plot_deq->second.back().GetPosition().y + Tile::kTileHeight };
}
