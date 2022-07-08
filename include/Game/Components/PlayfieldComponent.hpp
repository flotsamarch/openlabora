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

#ifndef PLAYFIELDCOMPONENT_HPP_
#define PLAYFIELDCOMPONENT_HPP_

#include <deque>
#include <optional>
#include <utility>
#include "Game/Plot.hpp"
#include "Misc/RangeWrapper.hpp"
#include "Misc/EnumMap.hpp"

namespace open_labora
{

namespace playfield
{

constexpr uint32_t kMaxFieldHeight{ 54u };
constexpr uint32_t kMaxFieldWidth{ 9u };

} // namespace playfield

class PlayfieldComponent final
{
    using PlotList = std::deque<Plot>;
    using PlotsMap = EnumMap<plot::Type, PlotList>;

    PlotsMap mPlots;

    static constexpr uint32_t kInitialPlotOffsetY{ 26u * tile::kTileHeight };

public:
    using PlotsIterConst = PlotList::const_iterator;
    using PlotsRange = RangeWrapper<PlotsIterConst>;

    PlayfieldComponent(const sf::Vector2f& position, IResourceManager::Ptr);

    void AddPlotToTop(const Plot&);

    void AddPlotToBottom(const Plot&);

    void AddPlotToTop(Plot&&);

    void AddPlotToBottom(Plot&&);

    PlotsRange GetPlots(plot::Type type) const { return { mPlots[type] }; }

    bool IsPlotsLimitReached(plot::Type) const;

    #if 0 // TODO: Reimplement Build Mode
    using OptionalTileInfo = std::optional<tile::TileInfo>;

    OptionalTileInfo GetTileInfoUnderPoint(const sf::Vector2f&) const;

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;
    #endif
};

} // namespace open_labora

#endif // PLAYFIELDCOMPONENT_HPP_
