#include "AppState/AppStateManager.hpp"

#include <concepts>
#include <cassert>
#include <GameState/Model.hpp>
#include "GameState/Views/GameView.hpp"
#include "GameState/Views/GVDuel.hpp"
#include "GameState/Views/GVMainMenu.hpp"
#include "GameState/Views/GVFinal.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "GameState/Controllers/GCDuel.hpp"
#include "GameState/Controllers/GCMainMenu.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

AppStateManager::AppStateManager(std::unique_ptr<IResourceManager> res_mgr,
                sf::Vector2u window_size)
    : mResourceManager{ std::move(res_mgr) }, mModel{ std::make_shared<Model>() }
{
    mModel->mWindowSize = window_size;
};

AppStateManager::~AppStateManager() = default;

void AppStateManager::Update(float update_delta_seconds)
{
    assert(mState.gv != nullptr);
    assert(mState.gc != nullptr);
    mState.gv->Update(update_delta_seconds);
    mState.gc->Update(update_delta_seconds);
}

void AppStateManager::HandleEvent(const sf::Event& evt)
{
    assert(mState.gv != nullptr);
    assert(mState.gc != nullptr);
    mState.gv->HandleEvent(evt);
    mState.gc->HandleEvent(evt);
}

template <class TStateName>
void AppStateManager::SetNextState()
{
    using view_t = typename TStateName::view_type;
    using ctlr_t = typename TStateName::controller_type;

    static_assert(std::is_base_of<IGameView, view_t>::value,
                  "view_type must inherit from GameView");
    static_assert(std::is_base_of<IGameController, ctlr_t>::value,
                  "controller_type must inherit from GameController");

    mNextState.gv = std::make_unique<view_t>(shared_from_this(),
                                             mState.gc, // This ptr might be a
                                             mModel);   // problem in the future
    mNextState.gc = std::make_unique<ctlr_t>(shared_from_this(), mModel);
}

void AppStateManager::ChangeState()
{
    mState.gv = std::move(mNextState.gv);
    mState.gc = std::move(mNextState.gc);
}

template void AppStateManager::SetNextState<AppStateDefs::FinalState>();
template void AppStateManager::SetNextState<AppStateDefs::MainMenuState>();
template void AppStateManager::SetNextState<AppStateDefs::DuelState>();

} // namespace OpenLabora
