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

#ifndef LOCATION_HPP_
#define LOCATION_HPP_

#include <map>
#include "Resource/IResourceManager.hpp"
#include "Entity.hpp"
#include "Playfield.hpp"
#include "Tile.hpp"

namespace open_labora
{

class Location final : public Entity<sf::Sprite>
{
public:
    enum class LocationType {
        Empty, Begin = Empty, Forest, Peat,
        HouseBoat, FishingVillage, ClayMound, End
    };

    using Ptr = std::shared_ptr<Location>;

    Location(LocationType);

    static bool IsPlaceableOn(LocationType, Tile::TileType);
    static std::string_view GetLocationName(LocationType type)
        { return kLocationNames.find(type)->second; }

    LocationType GetType() const noexcept { return mType; }

private:
    using LocationStrMap = std::map<LocationType, std::string_view>;
    using PlaceableMap = std::map<LocationType, Tile::TileType>;
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

inline Location::LocationType operator++ (Location::LocationType& type) {
    if (type == Location::LocationType::End) {
        return type;
    }
    type = static_cast<Location::LocationType>(static_cast<int>(type) + 1);
    return type;
}

} // namespace open_labora

#endif // LOCATION_HPP_
