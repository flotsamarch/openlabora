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

#include "GameState/Final.hpp"
#include "GameState/FinalFwd.hpp"
#include "ApplicationState/ApplicationContext.hpp"

namespace open_labora
{

void state::changeState(state::Final, ApplicationContext::Ptr app)
{ app->ChangeState<open_labora::Final>(); }

void stateUpdate(Final&, [[maybe_unused]]float update_delta_seconds)
{
}

void stateHandleInput(Final&, PtrView<const Input>)
{
}

DrawableRangeConst stateGetDrawableObjects(Final&)
{ return {}; }

bool stateGetFlagIsFinal(const Final&) noexcept
{ return true; }

} // namespace open_labora
