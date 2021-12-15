#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <unordered_map>
#include "resource/IResourceManager.hpp"
#include "GameObject.hpp"
#include "Tile.hpp"

class Location final : public GameObject
{
public:
    enum class LocationType {
        Empty, Forest, Peat, HouseBoat, FishingVillage, ClayMound
    };

    Location(const IResourceManager&, LocationType);

    static bool IsPlaceableOn(LocationType, Tile::TileType);
    static std::string_view GetLocationName(LocationType type)
        { return kLocationNames.find(type)->second; }

    LocationType GetType() const noexcept { return mType; }
    void SetType(LocationType);

private:
    using LocationStrMap = std::unordered_map<LocationType, std::string_view>;
    using PlaceableMap = std::unordered_map<LocationType, Tile::TileType>;
    LocationType mType;

    inline static const LocationStrMap kTextureNames
    {
        {Location::LocationType::Empty, "coin" },
        {Location::LocationType::Forest, "location" },
        {Location::LocationType::Peat, "peat" },
        {Location::LocationType::HouseBoat, "houseboat" },
        {Location::LocationType::FishingVillage, "fishing" },
        {Location::LocationType::ClayMound, "claymound" }
    };

    inline static const PlaceableMap kPlaceableMap
    {
        {Location::LocationType::Forest, Tile::TileType::Forest},
        {Location::LocationType::Peat, Tile::TileType::Peat},
        {Location::LocationType::HouseBoat, Tile::TileType::Water},
        {Location::LocationType::FishingVillage, Tile::TileType::Coast},
        {Location::LocationType::ClayMound, Tile::TileType::Hill}
    };

    inline static const LocationStrMap kLocationNames
    {
        {Location::LocationType::Empty, "Destroy" },
        {Location::LocationType::Forest, "Forest" },
        {Location::LocationType::Peat, "Peat" },
        {Location::LocationType::HouseBoat, "House Boat" },
        {Location::LocationType::FishingVillage, "Fishing Village" },
        {Location::LocationType::ClayMound, "Clay Mound" }
    };
};

#endif // LOCATION_HPP_
