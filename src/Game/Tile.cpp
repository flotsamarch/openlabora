#include "Game/Tile.hpp"

namespace OpenLabora
{

namespace tile
{

bool IsValid(Type type) noexcept { return type != Type::None; }

Type operator++(Type& type) noexcept
{
    if (type == Type::End) {
        return type;
    }
    type = static_cast<Type>(static_cast<int>(type) + 1);
    return type;
}

bool operator==(const TileInfo& lhs, const TileInfo& rhs)
{
    return !std::islessgreater(lhs.coord.x, rhs.coord.x) &&
        !std::islessgreater(lhs.coord.y, rhs.coord.y) &&
        lhs.type == rhs.type && lhs.valid == rhs.valid;
}

Type operator+(int lhs, const Type& rhs) noexcept
{
    const auto type_int = static_cast<int>(rhs) + lhs;
    if (type_int >= static_cast<int>(Type::End)) {
        return Type::End;
    }
    return static_cast<Type>(type_int);
}

Type operator+(const Type& lhs, int rhs) noexcept
{
    const auto type_int = static_cast<int>(lhs) + rhs;
    if (type_int >= static_cast<int>(Type::End)) {
        return Type::End;
    }
    return static_cast<Type>(type_int);
}

} // namespace tile

} // namespace OpenLabora
