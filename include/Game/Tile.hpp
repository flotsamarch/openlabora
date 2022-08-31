// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef TILE_HPP_
#define TILE_HPP_

#include <cassert>
#include <cmath>
#include <string_view>
#include <span>
#include "Misc/CommonTypedefs.hpp"
#include "Misc/EnumMap.hpp"
#include "LibTypedefs.hpp"

namespace open_labora
{

namespace tile
{

enum class Type
{
    None, Begin = None, Forest,
    Hill, MountainUpper, MountainLower,
    Water, Coast, Peat, End
};

constexpr uint kTileHeight{ 150u };
constexpr uint kTileWidth{ 100u };
constexpr uint kMaxFieldHeight{ 54u };
constexpr uint kMaxFieldWidth{ 9u };

inline bool IsValid(tile::Type type) noexcept
{ return type != tile::Type::None; }


// ----------------- DEFINE TEXTURE NAME FOR EACH TILE HERE --------------------
constexpr EnumMap<Type, std::string_view> kTileToTextureMap(
{
    { Type::None, "" },
    { Type::Forest, "forest" },
    { Type::Coast, "coast" },
    { Type::Water, "water" },
    { Type::Peat, "peat_empty" },
    { Type::Hill, "hill" },
    { Type::MountainUpper, "mountain_upper" },
    { Type::MountainLower, "mountain_lower" },
});

constexpr Type& operator++(Type& type) noexcept
{
    assert(type >= Type::Begin && type < Type::End);
    type = static_cast<Type>(static_cast<int>(type) + 1);
    return type;
}

constexpr Type operator++(Type& type, int) noexcept
{
    assert(type >= Type::Begin && type < Type::End);
    auto new_value = type;
    type = static_cast<Type>(static_cast<int>(type) + 1);
    return new_value;
}

constexpr Type operator+(int lhs, Type rhs) noexcept
{
    const auto result = static_cast<Type>(static_cast<int>(rhs) + lhs);
    assert(result >= Type::Begin && result <= Type::End);
    return result;
}

constexpr Type operator+(Type lhs, int rhs) noexcept
{
    const auto result = static_cast<Type>(static_cast<int>(lhs) + rhs);
    assert(result >= Type::Begin && result <= Type::End);
    return result;
}

constexpr std::string_view getTextureName(Type type) noexcept
{
    return tile::kTileToTextureMap[type];
}

} // namespace tile

struct TileInfo
{
    Vector2f coord{ 0.f, 0.f };
    tile::Type type{ tile::Type::None };
    bool valid{ false };
};

inline bool operator==(const TileInfo& lhs, const TileInfo& rhs)
{
    return !std::islessgreater(lhs.coord.x, rhs.coord.x) &&
        !std::islessgreater(lhs.coord.y, rhs.coord.y) &&
        lhs.type == rhs.type && lhs.valid == rhs.valid;
}

} // namespace open_labora

#endif // TILE_HPP_
