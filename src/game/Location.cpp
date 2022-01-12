#include <cassert>
#include "game/Location.hpp"

Location::Location(const IResourceManager& res_mgr, LocationType type)
    : mType{ type }, mResMgr{ res_mgr }
{
    SetType(LocationType::Empty);
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

void Location::SetType(LocationType type)
{
    mType = type;
    auto&& texture = kTextureNames.find(type);
    assert(texture != kTextureNames.end());
    mObject.setTexture(mResMgr.GetTextureByName(texture->second), true);
}
