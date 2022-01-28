#include "GameState/Controllers/GameController.hpp"
#include "AppState/AppStateManager.hpp"
#include "Game/ExpansionMarker.hpp"

namespace OpenLabora
{

GameController::GameController(std::shared_ptr<AppStateManager> state,
                               std::shared_ptr<Model> model,
                               size_t player_count)
    : mState{ state }, mModel{ model }
{
    auto&& res_mgr = state->GetResourceManager();
    mModel->mEntities.clear();
    mModel->mSelectableEntities.clear();

    for (size_t player{0}; auto&& pf : mModel->mPlayfields) {
        pf.reset();
        if (player < player_count) {
            pf = CreateEntity<Playfield>(res_mgr);
        }
    }
}

void GameController::HandleEvent([[maybe_unused]]const sf::Event& evt) {}

void GameController::HandleWindowResize(const sf::Vector2u& window_size)
{
    mModel->mWindowSize = window_size;
}

void GameController::Update([[maybe_unused]]const float update_delta_seconds) {}

void GameController::EnableBuildMode([[maybe_unused]]Location::LocationType type)
{
    // TODO fix build mode
    // mBuildGhost->SetType(type);
    // bBuildModeEnabled = true;
}

} // namespace OpenLabora
