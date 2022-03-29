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
