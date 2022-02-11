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
    mModel->ResetEntities();

    auto pf_width = static_cast<float>(Playfield::kMaxFieldWidth);
    auto pf_height = static_cast<float>(Playfield::kMaxFieldHeight);
    auto pf_margin = pf_width * Tile::kTileWidth + 3 * Tile::kTileWidth;
    for (uint32_t player{0}; auto&& pf : mModel->GetPlayfields()) {
        pf.reset();
        if (player < player_count) {
            pf = mModel->CreateEntity<Playfield>(res_mgr);
            auto win_size = static_cast<sf::Vector2f>(mModel->GetWindowSize());
            auto position = sf::Vector2f{ win_size.x / 2, win_size.y / 2 };
            position.x -= (pf_width / 2) * Tile::kTileWidth;
            position.x += static_cast<float>(pf_margin * player);
            position.y -= (pf_height / 2) * Tile::kTileHeight;
            pf->SetPosition(position);
            player++;
        }
    }
}

void GameController::HandleEvent(const sf::Event& evt)
{
    switch (evt.type) {
        case sf::Event::MouseButtonReleased:
        {
            if (mModel->IsEventIgnored(evt.type)) {
                mModel->IgnoreNextEvent(evt.type, false);
                break;
            }
        }
        default: {}
    }
}

void GameController::HandleWindowResize(const sf::Vector2u& window_size)
{
    mModel->SetWindowSize(window_size);
}

void GameController::Update([[maybe_unused]]const float update_delta_seconds) {}

void GameController::EnableBuildMode([[maybe_unused]]Location::LocationType type)
{
    // TODO fix build mode
    // mBuildGhost->SetType(type);
    // bBuildModeEnabled = true;
}

ISelectable::Ptr GameController::FindSelectableEntity(SelectableCIterator entity)
{
    auto entities =
        std::const_pointer_cast<const Model>(mModel)->GetSelectableEntities();
    auto dist = std::distance(entity, entities.end());
    return mModel->GetSelectableEntities()[dist];
}

void GameController::RemoveMarker(ExpansionMarker::Ptr marker)
{
    mModel->RemoveEntity(marker);
}

} // namespace OpenLabora
