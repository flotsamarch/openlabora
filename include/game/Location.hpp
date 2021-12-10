#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <unordered_map>
#include "resource/IResourceManager.hpp"
#include "GameObject.hpp"
#include "Tile.hpp"

class Location : public GameObject
{
public:
    enum class LocationType { Empty, Forest, Peat };

    Location(const IResourceManager&, LocationType);

    static bool IsPlaceableOn(LocationType, Tile::TileType);

    LocationType GetType() const noexcept { return mType; }

private:
    using TextureMap = std::unordered_map<LocationType, std::string_view>;
    using PlaceableMap = std::unordered_map<LocationType, Tile::TileType>;
    LocationType mType;

    inline static const TextureMap kTextureNames
    {
        {Location::LocationType::Empty, "coin" },
        {Location::LocationType::Forest, "location" },
        {Location::LocationType::Peat, "peat" }
    };

    inline static const PlaceableMap kPlaceableMap
    {
        {Location::LocationType::Forest, Tile::TileType::Forest},
        {Location::LocationType::Peat, Tile::TileType::Peat}
    };
};

#endif // LOCATION_HPP_
