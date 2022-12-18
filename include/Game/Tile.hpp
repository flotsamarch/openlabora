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

#include <cmath>
#include <string_view>
#include "Misc/EnumMap.hpp"
#include "Misc/IterableEnumUtilities.hpp"
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

constexpr int kTileHeight = 150;
constexpr int kTileWidth = 100;
constexpr int kMaxFieldHeight = 54;
constexpr int kMaxFieldWidth = 9;

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

constexpr std::string_view getTextureName(Type type) noexcept
{
    return tile::kTileToTextureMap[type];
}

} // namespace tile

struct TileInfo
{
    Vector2f coord{ 0.f, 0.f };
    tile::Type type{ tile::Type::None };
    bool valid = false;
};

inline bool operator==(const TileInfo& lhs, const TileInfo& rhs)
{
    return !std::islessgreater(lhs.coord.x, rhs.coord.x) &&
        !std::islessgreater(lhs.coord.y, rhs.coord.y) &&
        lhs.type == rhs.type && lhs.valid == rhs.valid;
}

} // namespace open_labora

#endif // TILE_HPP_
