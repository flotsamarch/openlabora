#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cmath>
#include "game/Playfield.hpp"
#include "resource/ResourceManager.hpp"

namespace OpenLabora
{

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
    plot_top.SetPosition(static_cast<float>(offset_x), 0);
    plot_bottom.SetPosition(static_cast<float>(offset_x), Tile::kTileHeight);
    PushPlotBack(plot_top);
    PushPlotBack(plot_bottom);

    mGroundTexture.create(Tile::kTileWidth * kMaxFieldWidth,
                          Tile::kTileHeight * kMaxFieldHeight);
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
    auto plot_index = static_cast<int>((plot_top - point.y) / Tile::kTileHeight);

    if (plot_index < 0 || plot_index > plot_deq->second.size()) {
        return Tile::kBadTile;
    }

    return plot_deq->second[plot_index].GetTileInfoUnderPoint(point);
}

std::tuple<sf::Vector2f, sf::Vector2f>
Playfield::GetExpansionMarkerPositions(Plot::PlotType type) const
{
    if (mPlots.empty()) {
        return kBadMarkers;
    }
    auto&& plot_deq = mPlots.find(type);
    if (plot_deq == mPlots.end() || plot_deq->second.empty()) {
        return kBadMarkers;
    }

    auto top_left_pos = plot_deq->second.front().GetPosition(); //.y,
    auto btm_left_pos = plot_deq->second.back().GetPosition(); //.y,

    // TODO should be 2 tiles for side plots
    return {{top_left_pos.x, top_left_pos.y - Tile::kTileHeight},
            {btm_left_pos.x, btm_left_pos.y + Tile::kTileHeight}};
}

} // namespace OpenLabora
