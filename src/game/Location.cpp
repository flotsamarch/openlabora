#include "game/Location.hpp"

Location::Location(const IResourceManager& res_mgr, LocationType type)
    : GameObject{ res_mgr, kTextureNames.find(type)->second },
      mType{ type }
{
}

bool Location::IsPlaceableOn(LocationType location_t,
                                    Tile::TileType tile_t)
{
    return kPlaceableMap.find(location_t)->second == tile_t;
}
