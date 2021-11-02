#include <cassert>

#include "state/StateMachine.hpp"

StateMachine::StateMachine(Application& app, State& state) :
    mApp{ app }, mState{ state }
{
}

State::State(State&& rhs) noexcept :
    mApp{ rhs.mApp }
{
    *this = std::move(rhs);
}

State& State::operator=(State&& rhs) noexcept
{
    if (&rhs != this) {
        mGameState.reset();
        mGameState = std::move(rhs.mGameState);
        mUiState.reset();
        mUiState = std::move(rhs.mUiState);
    }
    return *this;
}

void State::Update(float secondsSinceLastCall)
{
    mGameState->Update(secondsSinceLastCall);
    mUiState->Update(secondsSinceLastCall);
}

void State::HandleEvent(const sf::Event& evt)
{
    assert(mGameState != nullptr);
    assert(mUiState != nullptr);
    mGameState->HandleEvent(evt);
    mUiState->HandleEvent(evt);
}
/*
void StateMachine::UpdateState(const float secondsSinceLastUpdate)
{
    assert(mState.mGameState != nullptr);
    assert(mState.mUiState != nullptr);
    mState.mGameState->Update(secondsSinceLastUpdate);
    mState.mUiState->Update(secondsSinceLastUpdate);
}

void StateMachine::AdvanceCompleteState()
{
    assert(mState.mGameState != nullptr);
    assert(mState.mUiState != nullptr);
    if (!mState.mGameState->IsComplete() && !mState.mUiState->IsComplete()) {
        return;
    }

    mState = std::move(mNextState);
    PushState<StateInitializers::FinalState>();
}

bool StateMachine::HaveReachedFinalState() const noexcept {
    return mState.IsSameState<StateInitializers::FinalState>();
}
*/
