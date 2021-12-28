#include "state/gs/GameState.hpp"
#include "state/State.hpp"

GameState::GameState(std::shared_ptr<State> state) : mState{ state }
{
}
