#include <cassert>

#include "state/State.hpp"
#include "state/gs/GameState.hpp"
#include "state/ui/UIState.hpp"

State::State(State&& rhs) noexcept :
    mApp{ rhs.mApp }
{
    *this = std::move(rhs);
}

State& State::operator=(State&& rhs) noexcept
{
    if (&rhs != this) {
        std::swap(mGameState, rhs.mGameState);
        std::swap(mUiState, rhs.mUiState);
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
