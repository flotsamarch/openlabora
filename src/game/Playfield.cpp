#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cmath>
#include "game/Playfield.hpp"
#include "game/PlayfieldInitArray.hpp"
#include "resource/ResourceManager.hpp"

Playfield::Playfield(const IResourceManager& res_mgr) :
    mTiles{ kPlayfieldInitArray }, mResMgr{ res_mgr }
{
    std::unordered_map<Tile::TileType, sf::Texture> mTileTextures;

    mTileTextures[Tile::TileType::Forest] = res_mgr.GetTextureByName("forest");
    mTileTextures[Tile::TileType::Coast] = res_mgr.GetTextureByName("coast");
    mTileTextures[Tile::TileType::Water] = res_mgr.GetTextureByName("water");
    mTileTextures[Tile::TileType::Peat] = res_mgr.GetTextureByName("peat_empty");
    mTileTextures[Tile::TileType::Hill] = res_mgr.GetTextureByName("hill");
    mTileTextures[Tile::TileType::Mountain] = res_mgr.GetTextureByName("mountain");

    mGroundTexture.create(kTileWidth * kFieldWidth, kTileHeight * kFieldHeight);

    for (std::size_t row{0u}, col{0u}; auto& sub_array : mTiles) {
            sf::Sprite sprite;
            for (auto& item : sub_array) {
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
    mSprite.setTexture(mGroundTexture.getTexture(), true);
}

sf::Vector2f Playfield::SnapPointToTile(const sf::Vector2f& point) const noexcept
{
    auto indices = GetTileIndicesUnderPoint(point);

    if (indices == std::nullopt) {
        return GameObject::kOutOfBounds;
    }

    return sf::Vector2f{
        static_cast<float>(indices.value().x * kTileWidth),
        static_cast<float>(indices.value().y * kTileHeight)
    };
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


Playfield::LocationIter
Playfield::GetOrCreateLocationAt(const sf::Vector2u& indices,
                                 Location::LocationType type)
{
    auto&& itlocation = mLocations[indices.y].begin() + indices.x;
    auto&& location = *itlocation;

    if (location == nullptr) {
        location = std::make_unique<Location>(mResMgr, type);
        location->SetPosition(static_cast<float>(indices.x * kTileWidth),
                              static_cast<float>(indices.y * kTileHeight));
    }

    return itlocation;
}

Playfield::LocationIter
Playfield::GetLocationUnderPoint(const sf::Vector2f& point)
{
    auto indices = GetTileIndicesUnderPoint(point);

    if (indices == std::nullopt) {
        return mLocations.begin()->end();
    }

    return GetOrCreateLocationAt(indices.value());
}

bool Playfield::IsTileValidForPlacement(const sf::Vector2u& indices,
                                        Location::LocationType type) const
{
    auto&& location = mLocations[indices.y][indices.x];

    if (location != nullptr &&
        location->GetType() != Location::LocationType::Empty) {
        return false;
    }

    if (!Location::IsPlaceableOn(type,
                                 mTiles[indices.y][indices.x])) {
        return false;
    }

    return true;
}

void Playfield::ChangeLocationTypeAtPoint(const sf::Vector2f& point,
                                          Location::LocationType type)
{
    auto indices = GetTileIndicesUnderPoint(point);
    auto tile_coords = SnapPointToTile(point);

    if (indices == std::nullopt) {
        return;
    }

    if (!IsTileValidForPlacement(indices.value(), type)) {
        return;
    }

    auto&& location = *GetOrCreateLocationAt(indices.value(), type);
    if (location->GetType() != type) {
        location->SetType(type);
    }
    DrawLocationOnFieldTexture(*location);
}

void Playfield::DrawLocationOnFieldTexture(const Location& location)
{
    mGroundTexture.draw(location.GetSprite());
}
