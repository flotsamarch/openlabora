#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <unordered_map>
#include "resource/IResourceManager.hpp"
#include "Entity.hpp"
#include "ISelectable.hpp"
#include "Playfield.hpp"

class Location final : public Entity//, public ISelectable
{
public:
    enum class LocationType {
        Empty, Begin = Empty, Forest, Peat,
        HouseBoat, FishingVillage, ClayMound, End
    };

    Location(const IResourceManager&, LocationType);

    static bool IsPlaceableOn(LocationType, Playfield::TileType);
    static std::string_view GetLocationName(LocationType type)
        { return kLocationNames.find(type)->second; }

    LocationType GetType() const noexcept { return mType; }
    void SetType(LocationType);

    const sf::Drawable& GetDrawableObject() const noexcept override;
private:
    using LocationStrMap = std::unordered_map<LocationType, std::string_view>;
    using PlaceableMap = std::unordered_map<LocationType, Playfield::TileType>;
    LocationType mType;
    const IResourceManager& mResMgr;

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
        {Location::LocationType::Forest, Playfield::TileType::Forest},
        {Location::LocationType::Peat, Playfield::TileType::Peat},
        {Location::LocationType::HouseBoat, Playfield::TileType::Water},
        {Location::LocationType::FishingVillage, Playfield::TileType::Coast},
        {Location::LocationType::ClayMound, Playfield::TileType::Hill}
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

inline Location::LocationType operator++ (Location::LocationType& type) {
    if (type == Location::LocationType::End) {
        return type;
    }
    type = static_cast<Location::LocationType>(static_cast<int>(type) + 1);
    return type;
}
#endif // LOCATION_HPP_
