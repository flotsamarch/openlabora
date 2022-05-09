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

#ifndef APPSTATEDEFS_HPP_
#define APPSTATEDEFS_HPP_

#include "AppState.hpp"
#include "GameState/Model/Model.hpp"
#include "GameState/Model/NoModel.hpp"

#include "GameState/Views/GVMainMenu.hpp"
#include "GameState/Views/GVDuel.hpp"
#include "GameState/Views/GVFinal.hpp"

#include "GameState/Controllers/GCMainMenu.hpp"
#include "GameState/Controllers/GCDuel.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

// ----------------------- ADD ALL STATES HERE ----------------------------------
using MainMenuState = AppState<NoModel, GVMainMenu, GCMainMenu>;
using DuelState = AppState<Model, GVDuel, GCDuel>;
using FinalState = AppState<NoModel, GVFinal, GCFinal>;

using State = std::variant<MainMenuState, DuelState, FinalState>;

} // namespace OpenLabora


#endif // APPSTATEDEFS_HPP_
