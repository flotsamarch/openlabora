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

#ifndef SUBVIEWINITIALIZER_HPP_
#define SUBVIEWINITIALIZER_HPP_

#include "GameWindow.hpp"
#include "Misc/PtrView.hpp"

namespace OpenLabora
{

// Structure for uniform initialization of subviews
template<class TGui, class TWindow, class TGameController>
struct SubviewInitializer final
{
    using Window = GameWindow<TGui, TWindow>;
    using GameControllerPtr = typename TGameController::Ptr;
    Window game_window;
    GameControllerPtr game_controller;
    SubviewInitializer(Window window, GameControllerPtr controller)
        : game_window{ window }, game_controller{ controller } {};
};

} // namespace OpenLabora

#endif // SUBVIEWINITIALIZER_HPP_
