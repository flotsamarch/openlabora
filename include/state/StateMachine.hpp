#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include "state/State.hpp"
#include "state/gs/GameState.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/gs/GSDuelHotSeat.hpp"
#include "state/gs/GSTest.hpp"
#include "state/ui/UiState.hpp"
#include "state/ui/UISFinal.hpp"
#include "state/ui/UISMainMenu.hpp"
#include "state/ui/UISDuelHotSeat.hpp"
#include "state/ui/UISTest.hpp"

class Application;

// Helper struct and typedefs that store valid (GameState, UiState) pairs
namespace StateInitializers
{
    template <class TGameState, class TUiState>
    struct StatePair final {
        using gs_type = TGameState;
        using ui_type = TUiState;
    };

    using TestState = StatePair<GSTest, UISTest>;
    using FinalState = StatePair<GSFinal, UISFinal>;
    using MainMenuState = StatePair<GSMainMenu, UISMainMenu>;
    using DuelHotSeatState = StatePair<GSDuelHotSeat, UISDuelHotSeat>;
};

// Main game application state machine
class StateMachine final
{
    Application& mApp;
    State& mState;
public:
    StateMachine(Application& app, State& state) :
        mApp{ app }, mState{ state } {};
    ~StateMachine() = default;
    StateMachine(StateMachine&&) = delete;
    StateMachine& operator=(StateMachine&&) = delete;
    StateMachine(const StateMachine&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;

    template <class TStatePair>
    void ChangeState();
};

template <class TStatePair>
void StateMachine::ChangeState()
{
    mState = State{TStatePair{}, mApp, mState};
}

#endif // STATE_MACHINE_HPP_
