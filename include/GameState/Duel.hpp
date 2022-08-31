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

#ifndef DUEL_HPP_
#define DUEL_HPP_

#include "GameState/GameState.hpp"
#include "GameState/Model.hpp"
#include "GameState/GameController.hpp"
#include "GameState/Views/EscapeMenuView.hpp"
#include "GameState/ViewModels/EscapeMenuViewModel.hpp"
#include "GameState/Views/CameraView.hpp"
#include "GameState/ViewModels/CameraViewModel.hpp"
#include "GameState/Views/DrawableView.hpp"
#include "GameState/ViewModels/DrawableViewModel.hpp"

namespace open_labora
{

using DrawableBinding = VVMBinding<Model, DrawableView, DrawableViewModel>;
using EscapeMenuBinding = VVMBinding<Model, EscapeMenuView, EscapeMenuViewModel>;
using CameraBinding = VVMBinding<Model, CameraView, CameraViewModel>;

using Duel = GameState<GameController,
                       Model,
                       DrawableBinding,
                       EscapeMenuBinding,
                       CameraBinding>;

void stateUpdate(Duel&, float update_delta_seconds);

void stateHandleInput(Duel&, Input::PtrConst);

DrawableRangeConst stateGetDrawableObjects(Duel&);

bool stateGetFlagIsFinal(const Duel&) noexcept;

} // namespace open_labora

#endif // DUEL_HPP_
