#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>

class GameState; // GS
class GSMainMenu;
class GSFinal;
class GSTest;

// Helper struct and typedefs that store valid (GameState, UiState) pairs
namespace StateInitializers
{
    template <class TGameState, class TUiState>
    struct StatePair final {
        using gs_type = TGameState;
        using ui_type = TUiState;
    };

    using TestState = StatePair<GSTest, void*>;
    using FinalState = StatePair<GSFinal, void*>;
    using MainMenuState = StatePair<GSMainMenu, void*>;
};

// Main game application state machine
class StateMachine final
{
    class State final
    {
        std::unique_ptr<GameState> mGameState;
        // std::unique_ptr<UiState> mUiState;
    public:
        State() = delete;
        ~State();
        State(const State&) = delete;
        State& operator=(const State&) = delete;
        State(State&&) noexcept;
        State& operator=(State&&) noexcept;

        template <class TStatePair>
        State(TStatePair);
        template <class TStatePair>
        bool inline IsSameState() const noexcept;

        friend class StateMachine;
    };
    State mState{ StateInitializers::MainMenuState{} };
    State mNextState{ StateInitializers::FinalState{} };
public:
    StateMachine();
    ~StateMachine();
    StateMachine(StateMachine&&);
    StateMachine& operator=(StateMachine&&);
    StateMachine(const StateMachine&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;

    template <class TStatePair, class TStatePairNext>
    StateMachine(TStatePair, TStatePairNext);
    template <class TStatePair>
    void PushState();

    void AdvanceCompleteState();
    void UpdateState();
    void HandleEvent(const sf::Event& evt);
    bool HaveReachedFinalState() const noexcept;
};

extern template void StateMachine::PushState<StateInitializers::TestState>();
extern template void StateMachine::PushState<StateInitializers::FinalState>();
extern template void StateMachine::PushState<StateInitializers::MainMenuState>();
extern template StateMachine::StateMachine(StateInitializers::TestState, StateInitializers::FinalState);
extern template StateMachine::StateMachine(StateInitializers::FinalState, StateInitializers::FinalState);

#endif // STATE_MACHINE_HPP_
