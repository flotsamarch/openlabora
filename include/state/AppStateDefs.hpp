#ifndef APPSTATEDEFS_HPP_
#define APPSTATEDEFS_HPP_

class GSFinal;
class UISFinal;
class GSMainMenu;
class UISMainMenu;
class GSDuel;
class UISDuel;

// Helper struct and typedefs that store valid (GameState, UiState) pairs

template <class TGameState, class TUiState>
struct StatePair final {
    using gs_type = TGameState;
    using ui_type = TUiState;
};

namespace AppStateDefs
{

    using FinalState = StatePair<GSFinal, UISFinal>;
    using MainMenuState = StatePair<GSMainMenu, UISMainMenu>;
    using DuelState = StatePair<GSDuel, UISDuel>;
};

#endif // APPSTATEDEFS_HPP_
