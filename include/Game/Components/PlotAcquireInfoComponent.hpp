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

#ifndef PLOTACQUIREINFOCOMPONENT_HPP_
#define PLOTACQUIREINFOCOMPONENT_HPP_

#include "Game/Lot.hpp"

namespace open_labora
{

struct PlotAcquireInfoComponent final
{
    lot::Type lot_type;
    bool add_to_top = false;
};

} // namespace open_labora

#endif // PLOTACQUIREINFOCOMPONENT_HPP_
