#include "state/State.hpp"
#include "state/GameState.hpp"
#include "state/FinalState.hpp"
#include "state/TestState.hpp"

State::State() = default;
State::~State() = default;
State::State(State&&) = default;
State& State::operator=(State&&) = default;

template<class GS>
void State::SetupState()
{
    static_assert(std::is_base_of<GameState, GS>::value,
                  "CreateState(): GS must inherit from GameState");
    mGameState = std::make_unique<GS>();
}

bool State::HasFinished() const
{
    // TODO insert try-catch
    return mGameState != nullptr && mGameState->HasFinished();
}

void State::HandleEvent(const sf::Event &evt)
{
    // TODO insert try-catch
    mGameState->HandleEvent(evt);
}

void State::Update()
{
    // TODO insert try-catch
    mGameState->Update();
}

template void State::SetupState<FinalState>();
template void State::SetupState<TestState>();
