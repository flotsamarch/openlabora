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

#ifndef EXPANSIONMARKERCOMPONENT_HPP_
#define EXPANSIONMARKERCOMPONENT_HPP_

#include "Game/Plot.hpp"

namespace open_labora
{

namespace marker
{

enum class Type
{ Begin, Upper = Begin, Filling, Lower, End };

inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };

} // namespace marker

class ExpansionMarkerComponent final
{
    using PlotType = plot::Type;
    using Type = marker::Type;

    Type mType;
    Plot mPlot;
    Plot mPlotAlt;

public:
    ExpansionMarkerComponent(Type type,
                             const Plot& plot,
                             const Plot& plot_alt)
        : mType{ type }, mPlot{ plot }, mPlotAlt{ plot_alt } {};

    ExpansionMarkerComponent(Type type,
                             Plot&& plot,
                             Plot&& plot_alt)
        : mType{ type }, mPlot{ plot }, mPlotAlt{ plot_alt } {};

    plot::PlotsPair GetPlots() const
    { return { mPlot, mPlotAlt }; };

    Type GetType() const noexcept
    { return mType; }

    PlotType GetPlotType() const noexcept
    { return ecs::getComponent<PlotComponent>(mPlot).GetType(); }

    void SetPlotPositions(const sf::Vector2f& position) noexcept {
        plot::setPosition(mPlot, position);
        plot::setPosition(mPlotAlt, position, true);
    }

};

} // namespace open_labora

#endif // EXPANSIONMARKERCOMPONENT_HPP_
