#ifndef APPSTATEDEFS_HPP_
#define APPSTATEDEFS_HPP_

#include <concepts>
#include <GameState/Views/IGameView.hpp>
#include <GameState/Controllers/IGameController.hpp>

namespace OpenLabora
{

class GVFinal;
class GCFinal;
class GVMainMenu;
class GCMainMenu;
class GVDuel;
class GCDuel;

// Storage struct for holding valid combinations of Controller and View
// for every AppState. It allows in-place construction of app states
// while keeping them forward declared
template <class TGameView, class TGameController>
struct StateName final {
    using view_type = TGameView;
    using controller_type = TGameController;
};

namespace AppStateDefs
{
    using FinalState = StateName<GVFinal, GCFinal>;
    using MainMenuState = StateName<GVMainMenu, GCMainMenu>;
    using DuelState = StateName<GVDuel, GCDuel>;
};

} // namespace OpenLabora

#endif // APPSTATEDEFS_HPP_
