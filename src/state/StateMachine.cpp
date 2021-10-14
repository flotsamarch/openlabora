#include <cassert>

#include "state/StateMachine.hpp"
#include "state/gs/GameState.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/gs/GSTest.hpp"

StateMachine::State::~State() = default;

StateMachine::StateMachine() = default;
StateMachine::~StateMachine() = default;
StateMachine::StateMachine(StateMachine&&) = default;
StateMachine& StateMachine::operator=(StateMachine&&) = default;

template <class TStatePair>
StateMachine::State::State(TStatePair)
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    static_assert(std::is_base_of<GameState, gs_t>::value,
                  "CreateState(): GS must inherit from GameState");

    mGameState = std::make_unique<gs_t>();
    // mUiState = std::make_unique<ui_t>();
}

StateMachine::State::State(State&& rhs) noexcept
{
    *this = std::move(rhs);
}

StateMachine::State& StateMachine::State::operator=(State&& rhs) noexcept
{
    if (&rhs != this) {
        mGameState.reset();
        mGameState = std::move(rhs.mGameState);
    }
    return *this;
}

template <class TStatePair>
bool StateMachine::State::IsSameState() const noexcept
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    return dynamic_cast<const gs_t*>(mGameState.get()) != nullptr;
}

template <class TStatePair, class TStatePairNext>
StateMachine::StateMachine(TStatePair, TStatePairNext) :
    mState{ TStatePair{} }, mNextState{ TStatePairNext{} }
{
}

template <class TStatePair>
void StateMachine::PushState()
{
    mNextState = std::move(State(TStatePair{}));
}

void StateMachine::HandleEvent(const sf::Event &evt)
{
    assert(mState.mGameState != nullptr);
    mState.mGameState->HandleEvent(evt);
}

void StateMachine::UpdateState()
{
    assert(mState.mGameState != nullptr);
    mState.mGameState->Update();
}

void StateMachine::AdvanceCompleteState()
{
    assert(mState.mGameState != nullptr);
    if (!mState.mGameState->IsComplete()) {
        return;
    }

    mState = std::move(mNextState);
    PushState<StateInitializers::FinalState>();
}

bool StateMachine::HaveReachedFinalState() const noexcept {
    return mState.IsSameState<StateInitializers::FinalState>();
}

template void StateMachine::PushState<StateInitializers::TestState>();
template void StateMachine::PushState<StateInitializers::FinalState>();
template void StateMachine::PushState<StateInitializers::MainMenuState>();
template StateMachine::StateMachine(StateInitializers::TestState, StateInitializers::FinalState);
template StateMachine::StateMachine(StateInitializers::FinalState, StateInitializers::FinalState);
