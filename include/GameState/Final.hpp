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

#ifndef FINAL_HPP_
#define FINAL_HPP_

#include "Misc/PtrView.hpp"
#include "LibTypedefs.hpp"

namespace open_labora
{

class Input;
class ApplicationContext;

struct Final
{
    Final(PtrView<ApplicationContext>) {};
};

void stateUpdate(Final&, float update_delta_seconds);

void stateHandleInput(Final&, PtrView<const Input>);

DrawableRangeConst stateGetDrawableObjects(Final&);

bool stateGetFlagIsFinal(const Final&) noexcept;

} // namespace open_labora

#endif // FINAL_HPP_
