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

#include <string_view>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Misc/EnumMap.hpp"

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

constexpr uint32_t kTileHeight{ 150u };
constexpr uint32_t kTileWidth{ 100u };

struct TileInfo
{
    sf::Vector2f coord{ 0.f, 0.f };
    Type type{ Type::None };
    bool valid{ false };
};

bool IsValid(Type type) noexcept;

Type operator++(Type& type) noexcept;
bool operator==(const TileInfo& lhs, const TileInfo& rhs);
Type operator+(int lhs, const Type& rhs) noexcept;
Type operator+(const Type& lhs, int rhs) noexcept;

// ------------------- ADD TEXTURE NAME FOR EACH TILE HERE ---------------------

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

} // namespace tile

} // namespace open_labora

#endif // TILE_HPP_
