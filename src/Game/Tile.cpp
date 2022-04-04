#include "Game/Tile.hpp"

namespace OpenLabora
{

bool operator==(const Tile::TileInfo& lhs, const Tile::TileInfo& rhs)
{
    return !std::islessgreater(lhs.coord.x, rhs.coord.x) &&
        !std::islessgreater(lhs.coord.y, rhs.coord.y) &&
        lhs.type == rhs.type && lhs.valid == rhs.valid;
}

Tile::TileType operator+(int lhs, const Tile::TileType& rhs) noexcept
{
    const auto type_int = static_cast<int>(rhs) + lhs;
    if (type_int >= static_cast<int>(Tile::TileType::End)) {
        return Tile::TileType::End;
    }
    return static_cast<Tile::TileType>(type_int);
}

Tile::TileType operator+(const Tile::TileType& lhs, int rhs) noexcept
{
    const auto type_int = static_cast<int>(lhs) + rhs;
    if (type_int >= static_cast<int>(Tile::TileType::End)) {
        return Tile::TileType::End;
    }
    return static_cast<Tile::TileType>(type_int);
}

} // namespace OpenLabora
