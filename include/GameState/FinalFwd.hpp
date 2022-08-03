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

#ifndef FINALFWD_HPP_
#define FINALFWD_HPP_

#include "Misc/PtrView.hpp"

namespace open_labora
{

class ApplicationContext;

namespace state
{

// This is both id and the state because it contains no data and does nothing
struct Final
{
};

void changeState(Final, PtrView<ApplicationContext>);

} // namespace state


} // namespace open_labora

#endif // FINALFWD_HPP_
