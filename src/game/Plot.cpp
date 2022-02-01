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

    auto width = Tile::kTileWidth * static_cast<uint32_t>(mTiles.size());
    mPlotTexture->create(width, Tile::kTileHeight);
    mObject.setTexture(mPlotTexture->getTexture(), true);
    DrawTilesAsSprite();
}

uint32_t Plot::GetPlotWidthTileCount(PlotType type)
{
    assert(type != PlotType::End);
    return kPlotSizes[static_cast<size_t>(type)];
}

float Plot::GetOffsetXForPlotType(PlotType type)
{
    assert(type != PlotType::End);
    auto offset{ 0u };
    for (auto i = PlotType::Begin; i < type && i <PlotType::End; ++i) {
        offset += Tile::kTileWidth * static_cast<uint32_t>(GetPlotWidthTileCount(i));
    }
    return static_cast<float>(offset);
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
    mPlotTexture->clear();
    auto width = Tile::kTileWidth * static_cast<uint32_t>(mTiles.size());
    auto position = mObject.getPosition();
    auto view = sf::View({position.x, position.y,
            static_cast<float>(width), Tile::kTileHeight});
    mPlotTexture->setView(view);
    for (float offset_x = 0.f; auto&& tile : mTiles) {
        if (tile.IsValid()) {
            tile.SetPosition(position.x + offset_x, position.y);
            mPlotTexture->draw(tile.GetDrawableObject());
        }
        offset_x += Tile::kTileWidth;
    }
    mPlotTexture->display();
}

} // namespace OpenLabora
