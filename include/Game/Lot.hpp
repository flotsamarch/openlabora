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
#include <span>
#include "Tile.hpp"
#include "Resource/IResourceManager.hpp"
#include "Misc/IterableEnumUtilities.hpp"

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
    int value;

    constexpr SubtypeId(int subtype) noexcept
        : value{ subtype } {}

    constexpr explicit operator int() const noexcept
    { return static_cast<int>(value); }

    constexpr explicit operator size_t() const noexcept
    { return static_cast<size_t>(value); }
};

constexpr int kLotTypeCount
{ static_cast<int>(Type::End) - static_cast<int>(Type::Begin)};

static constexpr int kHeartlandOffsetY{ 26 * tile::kTileHeight };

// ------------------ DEFINE SUBTYPES FOR EACH LOT TYPE ------------------------
enum CoastalSubtypes : int
{
    kRegularCoast,
    kCoastalSubtypeCount // Must be the last. Represents the amount of entries
};

enum CentralSubtypes : int
{
    kCentralFFFFH, // Regular
    kCentralPFFHH, // Alternative
    kCentralPFFFH, // Initial 1
    kCentralPFFFF, // Initial 2
    kCentralSubtypeCount // Must be the last. Represents the amount of entries
};

enum MountainSubtypes : int
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
constexpr EnumMap<Type, int> kLotTileCount
{
    { Type::Coastal, 2 },
    { Type::Central, 5 },
    { Type::Mountain, 2 },
};

// ------------- DEFINE MAXIMUM AMOUNT OF LOTS FOR EACH LOT TYPE ---------------
constexpr EnumMap<Type, int> kMaximumLotCount
{
    { Type::Coastal, 18 },
    { Type::Central, 11 },
    { Type::Mountain, 18 },
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

constexpr int getTileCount(Type type)
{
    assert(type >= Type::Begin);
    assert(type < Type::End);
    return kLotTileCount[type];
}

constexpr int getMaximumCount(Type type)
{
    assert(type >= Type::Begin);
    assert(type < Type::End);
    return kMaximumLotCount[type];
}

constexpr Subtype getLotSubtypes(Type type)
{
    assert(type >= Type::Begin);
    assert(type < Type::End);
    return kLotTypeToSubtypes[type];
}

constexpr std::span<const std::string_view> getLotSubtypeTextureNames(Type type)
{
    assert(type >= Type::Begin);
    assert(type < Type::End);
    return kLotTypeToTextures[type];
}

constexpr float getOffsetX(Type type)
{
    assert(type >= Type::Begin);
    assert(type < Type::End);
    auto begin = kLotTileCount.cbegin();
    auto target = std::next(begin, static_cast<int>(type));

    auto accumulator = 0.f;
    auto add = [&accumulator] (auto value) { accumulator += value.second; };
    std::for_each(begin, target, add);

    return accumulator * tile::kTileWidth;
}

Sprite getSprite(Type, SubtypeId subtype, IResourceManager::Ptr);

// @return lot type whose lot count is used to calculate marker count for
// specified lot type.
constexpr Type getAnchorLotType(lot::Type type)
{
    if (type < lot::Type::Central) {
        return type + 1;
    } else if (type > lot::Type::Central) {
        return type - 1;
    } else {
        return type;
    }
}

} // namespace lot

} // namespace open_labora

#endif // LOT_HPP_
