#include "game/Location.hpp"

Location::Location(const IResourceManager& res_mgr, LocationType type)
    : GameObject{ res_mgr, kTextureNames.find(type)->second },
      mType{ type }
{
}

bool Location::IsPlaceableOn(LocationType location_t,
                                    Tile::TileType tile_t)
{
  auto result = kPlaceableMap.find(location_t);
  if (result == kPlaceableMap.end()) {
    return false;
  }
  return result->second == tile_t;
}