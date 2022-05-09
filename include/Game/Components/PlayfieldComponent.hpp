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

#include <list>
#include <optional>
#include "Game/Plot.hpp"
#include "Misc/RangeWrapper.hpp"

namespace OpenLabora
{

namespace playfield
{

constexpr uint32_t kMaxFieldHeight{ 54u };
constexpr uint32_t kMaxFieldWidth{ 9u };

} // namespace playfield

class PlayfieldComponent final
{
    using Plot = plot::Plot;
    using PlotList = std::list<Plot>;
    using PlotsMap = std::map<plot::Type, PlotList>;

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

    PlotsRange GetPlots(plot::Type) const;

    bool IsPlotsLimitReached(plot::Type) const;

    #if 0 // TODO: Reimplement Build Mode
    using OptionalTileInfo = std::optional<tile::TileInfo>;

    OptionalTileInfo GetTileInfoUnderPoint(const sf::Vector2f&) const;

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;
    #endif

    #if 0 // TODO: Reimplement markers (again)
    // @return positions for top and bottom expansion markers respectively for a
    // given plot type
    std::tuple<sf::Vector2f, sf::Vector2f>
    GetExpansionMarkerPositions(plot::Type) const;

    uint32_t GetDisposableMarkerCount(plot::Type) const;
    #endif
};

} // namespace OpenLabora

#endif // PLAYFIELDCOMPONENT_HPP_
