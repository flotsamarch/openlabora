#include <cassert>
#include <ranges>
#include <algorithm>
#include "game/Plot.hpp"

Plot::Plot(const PlotTilesAndType& ptat,
           const IResourceManager& res_mgr)
    : mType{ ptat.type }, mPlotTexture{ std::make_shared<sf::RenderTexture>() }
{
    std::ranges::for_each(ptat.tiles, [&res_mgr, this](Tile::TileType type) {
            mTiles.emplace_back(type, res_mgr);
        });

    DrawTilesAsSprite();
}

Tile::TileInfo Plot::GetTileInfoUnderPoint(const sf::Vector2f& point) const
{
    if (!IsUnderPoint(point)) {
        return Tile::kBadTile;
    }

    return mTiles[(point.y - GetPosition().y) / Tile::kTileWidth].GetTileInfo();
}

void Plot::DrawTilesAsSprite()
{
    mPlotTexture->create(Tile::kTileWidth * mTiles.size(), Tile::kTileHeight);
    for (float offset_x = 0.f; auto&& tile : mTiles) {
        if (tile.IsValid()) {
            tile.SetPosition(offset_x, 0.f);
            mPlotTexture->draw(tile.GetDrawableObject());
        }
        offset_x += Tile::kTileWidth;
    }
    mPlotTexture->display();
    mObject.setTexture(mPlotTexture->getTexture(), true);
}
