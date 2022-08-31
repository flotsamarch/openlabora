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

#ifndef PLOT_HPP_
#define PLOT_HPP_

#include "Lot.hpp"

namespace open_labora
{

// Plot is a collection of lot subtypes that are treated as a single entity
using Plot = std::span<const lot::SubtypeId>;

namespace plot
{

// Each predefined plot has its unique id
struct TypeId
{
    uint value;

    constexpr TypeId(int type) noexcept
        : value{ static_cast<uint>(type) } {}

    constexpr operator uint() const noexcept { return value; }
};

// ----------------- DEFINE PLOT TYPES FOR EACH LOT TYPE -----------------------
enum CoastalPlotTypes
{
    kCoastal,
    kCoastalPlotTypeCount // Must be the last. Represents the amount of entries
};

enum CentalPlotTypes
{
    kCentral,
    kCentralAlt,
    kCentralPlotTypeCount // Must be the last. Represents the amount of entries
};

enum MountainPlotTypes
{
    kMountain,
    kMountainPlotTypeCount // Must be the last. Represents the amount of entries
};

// ------------------ GROUP LOT SUBTYPES BY PLOT TYPES -------------------------
constexpr std::array<lot::SubtypeId, 2> kCoastalLotArray
{ lot::kRegularCoast, lot::kRegularCoast };

constexpr std::array<lot::SubtypeId, 1> kCentralLotArray
{ lot::kCentralFFFFH };

constexpr std::array<lot::SubtypeId, 1> kCentralAltLotArray
{ lot::kCentralPFFHH };

constexpr std::array<lot::SubtypeId, 2> kMountainLotArray
{ lot::kMountainTop, lot::kMountainBottom};

// -------------------- DEFINE PLOTS FOR EACH PLOT TYPE ------------------------
constexpr Plot kCoastalPlot
{ kCoastalLotArray };

constexpr Plot kCentralPlot
{ kCentralLotArray };

constexpr Plot kCentralAltPlot
{ kCentralAltLotArray };

constexpr Plot kMountainPlot
{ kMountainLotArray };

// ------------------------ GROUP PLOTS BY PLOT TYPE ---------------------------
constexpr std::array kCoastalPlotArray
{ kCoastalPlot };

constexpr std::array kCentralPlotArray
{ kCentralPlot, kCentralAltPlot };

constexpr std::array kMountainPlotArray
{ kMountainPlot };

// ---------------------- MAP LOT TYPES TO PLOT GROUPS -------------------------
constexpr EnumMap<lot::Type, std::span<const Plot>> kLotTypeToPlots
{
    { lot::Type::Coastal, kCoastalPlotArray },
    { lot::Type::Central, kCentralPlotArray },
    { lot::Type::Mountain, kMountainPlotArray },
};

constexpr std::span<const Plot> getPlots(lot::Type type)
{
    assert(type >= lot::Type::Begin && type < lot::Type::End);
    return kLotTypeToPlots[type];
}

} // namespace plot

} // namespace open_labora

#endif // PLOT_HPP_
