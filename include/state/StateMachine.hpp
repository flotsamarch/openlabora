#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "state/gs/GameState.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/gs/GSTest.hpp"
#include "state/ui/UiState.hpp"
#include "state/ui/UISFinal.hpp"
#include "state/ui/UISMainMenu.hpp"
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
};

class State final
{
    std::unique_ptr<GameState> mGameState;
    std::unique_ptr<UiState> mUiState;
    Application& mApp;
public:
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) noexcept;
    State& operator=(State&&) noexcept;

    template <class TStatePair>
    State(TStatePair, Application&);
    template <class TStatePair>
    bool inline IsSameState() const noexcept;

    Application& GetApplication() & noexcept { return mApp; }
    void Update(const float secondsSinceLastCall);
    void HandleEvent(const sf::Event&);

    friend class StateMachine;
};

// Main game application state machine
class StateMachine final
{
    Application& mApp;
    State& mState;
public:
    StateMachine(Application&, State&);
    ~StateMachine() = default;
    StateMachine(StateMachine&&) = delete;
    StateMachine& operator=(StateMachine&&) = delete;
    StateMachine(const StateMachine&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;

    template <class TStatePair>
    void ChangeState();
};

template <class TStatePair>
State::State(TStatePair, Application& app) : mApp { app }
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    static_assert(std::is_base_of<GameState, gs_t>::value,
                  "CreateState(): GS must inherit from GameState");

    mGameState = std::make_unique<gs_t>(*this);
    mUiState = std::make_unique<ui_t>(*this);
}

template <class TStatePair>
bool State::IsSameState() const noexcept
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    return dynamic_cast<const gs_t*>(mGameState.get()) != nullptr &&
        dynamic_cast<const ui_t*>(mUiState.get()) != nullptr;
}

template <class TStatePair>
void StateMachine::ChangeState()
{
    mState = State{TStatePair{}, mApp};
}

#endif // STATE_MACHINE_HPP_
