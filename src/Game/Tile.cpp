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

#include <cmath>
#include "Game/Tile.hpp"

namespace open_labora
{

namespace tile
{

bool IsValid(Type type) noexcept { return type != Type::None; }

Type operator++(Type& type) noexcept
{
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

} // namespace open_labora
