#include "state/State.hpp"

#include <cassert>
#include "state/gs/GameState.hpp"
#include "state/ui/UiState.hpp"

void State::Update(float secondsSinceLastCall)
{
    assert(mGameState != nullptr);
    assert(mUiState != nullptr);
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
