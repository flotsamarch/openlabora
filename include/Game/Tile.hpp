#ifndef TILE_HPP_
#define TILE_HPP_

#include <cassert>
#include <cmath>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <map>
#include "Resource/IResourceManager.hpp"
#include "Entity.hpp"

namespace OpenLabora
{

class Tile final : public Entity<sf::Sprite>
{
public:
    enum class TileType
    {
        None, Begin = None, Forest,
        Hill, MountainUpper, MountainLower, Water, Coast,
        Peat, End
    };

private:
    TileType mType{ TileType::None };

public:
    struct TileInfo
    {
        sf::Vector2f coord{ 0.f, 0.f };
        TileType type{ TileType::None };
        bool valid{ false };
    };

    static constexpr uint32_t kTileHeight{ 150u };
    static constexpr uint32_t kTileWidth{ 100u };

    using TileToTextureNameMap = const std::map<TileType, std::string_view>;

    inline static const TileToTextureNameMap kTileToTextureMap
    {
        { TileType::Forest, "forest" },
        { TileType::Coast, "coast" },
        { TileType::Water, "water" },
        { TileType::Peat, "peat_empty" },
        { TileType::Hill, "hill" },
        { TileType::MountainUpper, "mountain_upper" },
        { TileType::MountainLower, "mountain_lower" }
    };

    Tile(TileType type, IResourceManager::Ptr res_mgr)
        : mType{ type }
    {
        if (type != TileType::None) {
            auto iter = kTileToTextureMap.find(type);
            assert(iter != kTileToTextureMap.end());
            auto texture_name = iter->second;
            mObject.setTexture(res_mgr->GetTextureByName(texture_name));
            mObject.setTextureRect(sf::IntRect{ 0, 0, kTileWidth, kTileHeight });
        }
    };

    TileInfo GetTileInfo() const
    { return TileInfo{ mObject.getPosition(), mType, true }; }

    bool IsValid() const noexcept { return mType != TileType::None; }
};


inline Tile::TileType operator++ (Tile::TileType& type) noexcept {
    if (type == Tile::TileType::End) {
        return type;
    }
    type = static_cast<Tile::TileType>(static_cast<int>(type) + 1);
    return type;
}

bool operator==(const Tile::TileInfo& lhs, const Tile::TileInfo& rhs);
Tile::TileType operator+(int lhs, const Tile::TileType& rhs) noexcept;
Tile::TileType operator+(const Tile::TileType& lhs, int rhs) noexcept;

} // namespace OpenLabora

#endif // TILE_HPP_
