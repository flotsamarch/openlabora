#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include <algorithm>
#include <cmath>
#include "game/Playfield.hpp"
#include "game/PlayfieldInitArray.hpp"
#include "resource/ResourceManager.hpp"

Playfield::Playfield(const IResourceManager& res_mgr) :
    GameObject{ res_mgr }, mTiles{ kPlayfieldInitArray }
{
    std::unordered_map<Tile::TileType, sf::Texture> mTileTextures;

    mTileTextures[Tile::TileType::Forest] = res_mgr.GetTextureByName("forest");

    mFieldTexture.create(kTileWidth * kFieldWidth, kTileHeight * kFieldHeight);

    for (std::size_t row{0u}, col{0u}; auto& sub_array : mTiles) {
            sf::Sprite sprite;
            for (auto& item : sub_array) {
            sprite.setTexture(mTileTextures[item], true);
            float left = static_cast<float>(kTileWidth * col);
            float top = static_cast<float>(kTileHeight * row);
            sprite.setPosition(left, top);
            mFieldTexture.draw(sprite);
            col++;
        }
        row++;
        col = 0u;
    }

    for (std::size_t row{0u}, col{0u}; auto& sub_array : mLocations) {
        for (auto& item : sub_array) {
            item = std::make_unique<Location>(
                res_mgr, Location::LocationType::Empty);
            float left = static_cast<float>(kTileWidth * col);
            float top = static_cast<float>(kTileHeight * row);
            item->SetPosition(left, top);
            col++;
        }
        row++;
        col = 0u;
    }

    mFieldTexture.display();

    mSprite.setTexture(mFieldTexture.getTexture(), true);
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
Playfield::GetLocationAt(const sf::Vector2u& indices) const
{
    return mLocations[indices.y].begin() + indices.x;
}

Playfield::LocationIter
Playfield::GetLocationUnderPoint(const sf::Vector2f& point) const
{
    auto indices = GetTileIndicesUnderPoint(point);

    if (indices == std::nullopt) {
        return mLocations.begin()->end();
    }

    return GetLocationAt(indices.value());
}

bool Playfield::IsTileValidForPlacement(const sf::Vector2u& indices,
                                        Location::LocationType type) const
{
    auto& location = *GetLocationAt(indices);

    if (location->GetType() != Location::LocationType::Empty) {
        return false;
    }

    if (!Location::IsPlaceableOn(type,
                                 mTiles[indices.y][indices.x])) {
        return false;
    }

    return true;
}

void Playfield::CreateLocationAtPoint(const sf::Vector2f& point,
                                      Location::LocationType type,
                                      const IResourceManager& res_mgr)
{
    auto indices = GetTileIndicesUnderPoint(point);
    auto tile_coords = SnapPointToTile(point);

    assert (indices != std::nullopt); // Sanity check

    if (!IsTileValidForPlacement(indices.value(), type)) {
        return;
    }

    auto& location = mLocations[indices.value().y][indices.value().x];
    auto position = location->GetSprite().getPosition();
    location = std::make_unique<Location>(res_mgr, type);
    location->SetPosition(position);
    DrawLocationOnFieldTexture(*location);
}

void Playfield::DrawLocationOnFieldTexture(const Location& location)
{
    mFieldTexture.draw(location.GetSprite());
}
