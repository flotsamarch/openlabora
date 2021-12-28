#include "state/State.hpp"

#include <cassert>
#include "state/gs/GameState.hpp"
#include "state/ui/UiState.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/ui/UISMainMenu.hpp"
#include "state/gs/GSDuel.hpp"
#include "state/ui/UISDuel.hpp"

void State::Update(float secondsSinceLastCall, IRenderer& renderer)
{
    assert(mState.gs != nullptr);
    assert(mState.uis != nullptr);
    mState.gs->Update(secondsSinceLastCall, renderer);
    mState.uis->Update(secondsSinceLastCall);
}

void State::HandleEvent(const sf::Event& evt, IRenderer& renderer)
{
    assert(mState.gs != nullptr);
    assert(mState.uis != nullptr);
    mState.gs->HandleEvent(evt, renderer);
    mState.uis->HandleEvent(evt);
}

template <class TStatePair>
void State::SetNextState()
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    static_assert(std::is_base_of<IGameState, gs_t>::value,
                  "CreateState(): GS must inherit from GameState");
    static_assert(std::is_base_of<IUiState, ui_t>::value,
                  "CreateState(): GS must inherit from GameState");

    mNextState.gs = std::make_unique<gs_t>(shared_from_this());
    mNextState.uis = std::make_unique<ui_t>(shared_from_this(), mVideoMode);
}

void State::ChangeState()
{
    mState.gs = std::move(mNextState.gs);
    mState.uis = std::move(mNextState.uis);
}

template void State::SetNextState<AppStateDefs::FinalState>();
template void State::SetNextState<AppStateDefs::MainMenuState>();
template void State::SetNextState<AppStateDefs::DuelState>();
