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

#ifndef LOT_HPP_
#define LOT_HPP_

#include <functional>
#include <numeric>
#include "Tile.hpp"
#include "Resource/IResourceManager.hpp"
#include "Misc/CommonTypedefs.hpp"

namespace open_labora
{

// Lot is a horizontal collection of tiles
using Lot = std::span<const tile::Type>;

namespace lot
{

enum class Type
{
    Begin, Coastal = Begin, Central, Mountain, End
};

// Subtype is a predefined lot
using Subtype = std::span<const Lot>;

// Each predefined lot has its unique id
struct SubtypeId
{
    uint value;

    constexpr SubtypeId(int subtype) noexcept
        : value{ static_cast<uint>(subtype) } {}

    constexpr operator uint() const noexcept { return value; }
};

constexpr size_t kLotTypeCount
{ static_cast<size_t>(Type::End) - static_cast<size_t>(Type::Begin)};

static constexpr uint kHeartlandOffsetY{ 26u * tile::kTileHeight };

// ------------------ DEFINE SUBTYPES FOR EACH LOT TYPE ------------------------
enum CoastalSubtypes
{
    kRegularCoast,
    kCoastalSubtypeCount // Must be the last. Represents the amount of entries
};

enum CentralSubtypes
{
    kCentralFFFFH, // Regular
    kCentralPFFHH, // Alternative
    kCentralPFFFH, // Initial 1
    kCentralPFFFF, // Initial 2
    kCentralSubtypeCount // Must be the last. Represents the amount of entries
};

enum MountainSubtypes
{
    kMountainTop,
    kMountainBottom,
    kMountainSubtypeCount // Must be the last. Represents the amount of entries
};

// -------------------- DEFINE TILES FOR EACH LOT SUBTYPE ----------------------
constexpr std::array kCoastalLotTiles
{ tile::Type::Water, tile::Type::Coast };

constexpr std::array kCentralLotTiles
{
    tile::Type::Forest, tile::Type::Forest, tile::Type::Forest,
    tile::Type::Forest, tile::Type::Hill
};

constexpr std::array kCentralAltLotTiles
{
    tile::Type::Peat,
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Hill, tile::Type::Hill
};

constexpr std::array kHeartlandTopLotTiles
{
    tile::Type::Peat, tile::Type::Forest,
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Hill
};

constexpr std::array kHeartlandBottomLotTiles
{
    tile::Type::Peat,
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Forest, tile::Type::Forest
};

constexpr std::array kMountainTopLotTiles
{ tile::Type::Hill, tile::Type::MountainUpper };

constexpr std::array kMountainBottomLotTiles
{ tile::Type::Hill, tile::Type::MountainLower };

constexpr Lot kCoastalLot{ kCoastalLotTiles };
constexpr Lot kCentralLot{ kCentralLotTiles };
constexpr Lot kCentralAltLot{ kCentralAltLotTiles };
constexpr Lot kHeartlandTopLot{ kHeartlandTopLotTiles };
constexpr Lot kHeartlantBottomLot{ kHeartlandBottomLotTiles };
constexpr Lot kMountainTopLot{ kMountainTopLotTiles };
constexpr Lot kMountainBottomLot{ kMountainBottomLotTiles };

// -------------------- DEFINE TILE COUNT FOR EACH LOT -------------------------
constexpr EnumMap<Type, uint> kLotTileCount
{
    { Type::Coastal, 2u },
    { Type::Central, 5u },
    { Type::Mountain, 2u },
};

// ------------- DEFINE MAXIMUM AMOUNT OF LOTS FOR EACH LOT TYPE ---------------
constexpr EnumMap<Type, uint> kMaximumLotCount
{
    { Type::Coastal, 18u },
    { Type::Central, 11u },
    { Type::Mountain, 18u },
};

// ----------------------- GROUP LOTS BY LOT SUBTYPE ---------------------------
constexpr std::array<Lot, kCoastalSubtypeCount> kCoastalLotSubtypes
{
    kCoastalLot,
};

constexpr std::array<Lot, kCentralSubtypeCount> kCentralLotSubtypes
{
    kCentralLot,
    kCentralAltLot,
    kHeartlandTopLot,
    kHeartlantBottomLot,
};

constexpr std::array<Lot, kMountainSubtypeCount> kMountainLotSubtypes
{
    kMountainTopLot,
    kMountainBottomLot,
};

// ---------------------- MAP EACH LOT TYPE TO LOT GROUP -----------------------
constexpr EnumMap<Type, Subtype> kLotTypeToSubtypes
{
    { Type::Coastal, { kCoastalLotSubtypes } },
    { Type::Central, { kCentralLotSubtypes } },
    { Type::Mountain, { kMountainLotSubtypes } },
};

// ----------------- DEFINE TEXTURE ID FOR EACH LOT SUBTYPE -------------------
constexpr std::string_view kCoastalLotTextureName = "coastal_lot";
constexpr std::string_view kCentralLotTextureName = "central_lot";
constexpr std::string_view kCentralAltLotTextureName = "central_alt_lot";
constexpr std::string_view kHeartlandTopLotTextureName = "heartland_top_lot";
constexpr std::string_view kHeartlandBottomLotTextureName = "heartland_btm_alt";
constexpr std::string_view kMountainTopLotTextureName = "mountain_top_lot";
constexpr std::string_view kMountainBottomLotTextureName = "mountain_btm_lot";

// ----------------------- GROUP TEXTURE IDS BY LOT TYPE -----------------------
constexpr std::array<std::string_view, kCoastalSubtypeCount> kCoastalLotTextures
{
    kCoastalLotTextureName,
};

constexpr std::array<std::string_view, kCentralSubtypeCount> kCentralLotTextures
{
    kCentralLotTextureName,
    kCentralAltLotTextureName,
    kHeartlandTopLotTextureName,
    kHeartlandBottomLotTextureName,
};

constexpr
std::array<std::string_view, kMountainSubtypeCount> kMountainLotTextures
{
    kMountainTopLotTextureName,
    kMountainBottomLotTextureName,
};

// ----------------------- MAP LOT TYPES TO TEXTURES ---------------------------
constexpr EnumMap<Type, std::span<const std::string_view>> kLotTypeToTextures
{
    { Type::Coastal, { kCoastalLotTextures } },
    { Type::Central, { kCentralLotTextures } },
    { Type::Mountain, { kMountainLotTextures } },
};

constexpr uint getTileCount(Type type)
{
    assert(type >= Type::Begin && type < Type::End);
    return kLotTileCount[type];
}

constexpr Subtype getLotSubtypes(Type type)
{
    assert(type >= Type::Begin && type < Type::End);
    return kLotTypeToSubtypes[type];
}

constexpr std::span<const std::string_view> getLotSubtypeTextureNames(Type type)
{
    assert(type >= Type::Begin && type < Type::End);
    return kLotTypeToTextures[type];
}

constexpr float getOffsetX(Type type)
{
    assert(type >= Type::Begin && type < Type::End);
    auto begin = kLotTileCount.cbegin();
    auto target = std::next(begin, static_cast<int>(type));
    auto plus = [] (auto&& lhs, auto&& rhs) { return lhs + rhs.second; };

    return std::accumulate(begin, target, 0.f, plus) * tile::kTileWidth;
}

Sprite getSprite(Type, SubtypeId subtype, IResourceManager::Ptr);

constexpr Type& operator++(Type& type) noexcept
{
    assert(type >= Type::Begin && type < Type::End);
    type = static_cast<Type>(static_cast<int>(type) + 1);
    return type;
}

constexpr Type operator++(Type& type, int) noexcept
{
    assert(type >= Type::Begin && type < Type::End);
    auto new_value = type;
    type = static_cast<Type>(static_cast<int>(type) + 1);
    return new_value;
}

constexpr Type operator+(int lhs, Type rhs) noexcept
{
    const auto result = static_cast<Type>(static_cast<int>(rhs) + lhs);
    assert(result >= Type::Begin && result <= Type::End);
    return result;
}

constexpr Type operator+(Type lhs, int rhs) noexcept
{
    const auto result = static_cast<Type>(static_cast<int>(lhs) + rhs);
    assert(result >= Type::Begin && result <= Type::End);
    return result;
}

} // namespace lot

} // namespace open_labora

#endif // LOT_HPP_
