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

#include <cassert>
#include "Game/Location.hpp"

namespace OpenLabora
{

Location::Location(LocationType type)
    : mType{ type }
{
    // SetType(LocationType::Empty);
}

bool Location::IsPlaceableOn(LocationType location_t, Tile::TileType tile_t)
{
    auto result = kPlaceableMap.find(location_t);
    if (result == kPlaceableMap.end()) {
        return false;
    }
    return result->second == tile_t;
}

} // namespace OpenLabora
