#include "GameState/Controllers/GameController.hpp"
#include "AppState/AppStateManager.hpp"

namespace OpenLabora
{

GameController::GameController(std::shared_ptr<AppStateManager> state,
                               std::shared_ptr<Model> model,
                               uint32_t player_count)
    : mState{ state }, mModel{ model }
{
    auto&& res_mgr = state->GetResourceManager();
    mModel->mEntities.clear();
    mModel->mSelectableEntities.clear();

    auto pf_width = static_cast<float>(Playfield::kMaxFieldWidth);
    auto pf_height = static_cast<float>(Playfield::kMaxFieldHeight);
    auto pf_margin = pf_width * Tile::kTileWidth + 3 * Tile::kTileWidth;
    for (uint32_t player{0}; auto&& pf : mModel->mPlayfields) {
        pf.reset();
        if (player < player_count) {
            pf = CreateEntity<Playfield>(res_mgr);
            auto position =
                sf::Vector2f{ static_cast<float>(mModel->mWindowSize.x) / 2,
                              static_cast<float>(mModel->mWindowSize.y) / 2 };
            position.x -= (pf_width / 2) * Tile::kTileWidth;
            position.x += static_cast<float>(pf_margin * player);
            position.y -= (pf_height / 2) * Tile::kTileHeight;
            pf->SetPosition(position);
            player++;
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
