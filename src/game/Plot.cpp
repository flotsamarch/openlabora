#include <cassert>
#include <ranges>
#include <algorithm>
#include "game/Plot.hpp"

namespace OpenLabora
{

Plot::Plot(const PlotTilesAndType& ptat,
           const IResourceManager& res_mgr)
    : mType{ ptat.type }, mPlotTexture{ std::make_shared<sf::RenderTexture>() }
{
    std::ranges::for_each(ptat.tiles,
                          [&res_mgr, this]
                          (Tile::TileType type)
                          {
                              mTiles.emplace_back(type, res_mgr);
                          });

    DrawTilesAsSprite();
}

uint32_t Plot::GetPlotWidthTileCount(PlotType type)
{
    assert(type != PlotType::End);
    return kPlotSizes[static_cast<size_t>(type)];
}

uint32_t Plot::GetOffsetXForPlotType(PlotType type)
{
    assert(type != PlotType::End);
    auto offset{ 0u };
    for (auto i = PlotType::Begin; i < PlotType::End; ++i) {
        offset += Tile::kTileWidth * static_cast<uint32_t>(GetPlotWidthTileCount(i));
    }
    return offset;
}

Tile::TileInfo Plot::GetTileInfoUnderPoint(const sf::Vector2f& point) const
{
    if (!IsUnderPoint(point)) {
        return Tile::kBadTile;
    }

    auto index = (point.y - GetPosition().y) / Tile::kTileWidth;
    return mTiles[static_cast<size_t>(index)].GetTileInfo();
}

void Plot::DrawTilesAsSprite()
{
    auto width = Tile::kTileWidth * static_cast<uint32_t>(mTiles.size());
    mPlotTexture->create(width, Tile::kTileHeight);
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

} // namespace OpenLabora
