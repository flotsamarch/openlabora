#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cmath>
#include "game/Playfield.hpp"
#include "game/PlayfieldInitArray.hpp"
#include "resource/ResourceManager.hpp"

namespace
{
    using TileInfo = Playfield::TileInfo;
}

Playfield::Playfield(const IResourceManager& res_mgr) :
    mTiles{ kPlayfieldInitArray }, mResMgr{ res_mgr }
{
    mObject = std::make_unique<sf::Sprite>();
    std::unordered_map<TileType, sf::Texture> mTileTextures;

    mTileTextures[TileType::Forest] = res_mgr.GetTextureByName("forest");
    mTileTextures[TileType::Coast] = res_mgr.GetTextureByName("coast");
    mTileTextures[TileType::Water] = res_mgr.GetTextureByName("water");
    mTileTextures[TileType::Peat] = res_mgr.GetTextureByName("peat_empty");
    mTileTextures[TileType::Hill] = res_mgr.GetTextureByName("hill");
    mTileTextures[TileType::Mountain] = res_mgr.GetTextureByName("mountain");

    mGroundTexture.create(kTileWidth * kFieldWidth, kTileHeight * kFieldHeight);

    for (std::size_t row{0u}, col{0u}; auto& sub_array : mTiles) {
            sf::Sprite sprite;
            for (auto& item : sub_array) {
                if (item == TileType::None) {
                    continue;
                }
                sprite.setTexture(mTileTextures[item], true);
                float left = static_cast<float>(kTileWidth * col);
                float top = static_cast<float>(kTileHeight * row);
                sprite.setPosition(left, top);
                mGroundTexture.draw(sprite);
                col++;
        }
        row++;
        col = 0u;
    }

    mGroundTexture.display();
    static_cast<sf::Sprite*>(mObject.get())->
        setTexture(mGroundTexture.getTexture(), true);
}

TileInfo Playfield::GetTileInfoUnderPoint(const sf::Vector2f& point) const
{

    auto indices = GetTileIndicesUnderPoint(point);

    if (indices == std::nullopt) {
        return kBadTile;
    }

    auto tile_info = TileInfo{};
    tile_info.indices = indices.value();
    tile_info.coord = sf::Vector2f{
        static_cast<float>(tile_info.indices.x * kTileWidth),
        static_cast<float>(tile_info.indices.y * kTileHeight)
    };
    tile_info.type = mTiles[tile_info.indices.y][tile_info.indices.x];

    return tile_info;
}

std::optional<sf::Vector2u>
Playfield::GetTileIndicesUnderPoint(const sf::Vector2f& point) const noexcept
{
    if (point.x < 0 || point.y < 0
        || point.x > kTileWidth * kFieldWidth
        || point.y > kTileHeight * kFieldHeight) {
        return {};
    }

    return sf::Vector2u{
        static_cast<unsigned int>(std::trunc(point.x / kTileWidth)),
        static_cast<unsigned int>(std::trunc(point.y / kTileHeight))
    };
}

bool operator==(const Playfield::TileInfo& lhs,
                const Playfield::TileInfo& rhs)
{
    return lhs.coord == rhs.coord &&
        lhs.indices == rhs.indices &&
        lhs.type == rhs.type;
}
