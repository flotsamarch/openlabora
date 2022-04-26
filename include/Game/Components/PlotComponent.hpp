#ifndef PLOTCOMPONENT_HPP_
#define PLOTCOMPONENT_HPP_

#include <span>
#include "Game/Tile.hpp"

namespace OpenLabora
{

namespace plot
{

enum class Type
{
    Begin, Coastal = Begin, Central, Mountain, End
};

inline Type operator++ (Type& type)
{
    type = static_cast<Type>(static_cast<int>(type) + 1);
    return type;
}

inline Type operator+(int lhs, const Type& rhs) noexcept
{
    const auto type_int = static_cast<int>(rhs) + lhs;
    if (type_int >= static_cast<int>(Type::End)) {
        return Type::End;
    }
    return static_cast<Type>(type_int);
}

inline Type operator+(const Type& lhs, int rhs) noexcept
{
    const auto type_int = static_cast<int>(lhs) + rhs;
    if (type_int >= static_cast<int>(Type::End)) {
        return Type::End;
    }
    return static_cast<Type>(type_int);
}

using TileSpan = std::span<const tile::Type>;

} // namespace plot

class PlotComponent final
{
    using TileSpan = plot::TileSpan;
    using Type = plot::Type;

    TileSpan mTiles;
    Type mType;
    bool bIsAlternative;

public:
    PlotComponent(TileSpan tiles, Type type, bool is_alternative)
        : mTiles{ tiles }, mType{ type }, bIsAlternative{ is_alternative } {}

    #if 0 // TODO: Reimplement Build Mode these
    OptionalTileInfo GetTileInfoUnderPoint(const sf::Vector2f& point) const;
    #endif

    Type GetType() const noexcept { return mType; }

    uint32_t GetTileCount() const noexcept
    { return static_cast<uint32_t>(mTiles.size()); }

    const TileSpan& GetTiles() const noexcept { return mTiles; }

    bool IsAlternative() const noexcept { return bIsAlternative; }

};

} // namespace OpenLabora

#endif // PLOTCOMPONENT_HPP_
