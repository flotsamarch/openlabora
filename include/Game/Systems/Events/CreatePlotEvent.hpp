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

#ifndef CREATEPLOTEVENT_HPP_
#define CREATEPLOTEVENT_HPP_

#include "Game/Plot.hpp"

namespace open_labora
{

struct CreatePlotEvent
{
    Plot plot;
    lot::Type lot_type;
    bool to_top = false;
    Vector2f position{ 0.f, 0.f }; // Requested plot position.
                                   // Used only for the first plot of a type
    // TODO Multiplayer: Player affiliation
};

} // namespace open_labora

#endif // CREATEPLOTEVENT_HPP_
