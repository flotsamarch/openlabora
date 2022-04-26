#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

GameController::GameController(PtrView<IApplication<StateIdsVariant>> app,
                               IResourceManager::Ptr res_manager,
                               Model::Ptr model,
                               uint32_t player_count)
    : mApp { app }, mModel{ model }, mResManager{ res_manager }
{
    auto pf_width = static_cast<float>(playfield::kMaxFieldWidth);
    auto pf_margin = pf_width * tile::kTileWidth + 3 * tile::kTileWidth;

    for (uint32_t player{0}; auto&& pf : mModel->GetPlayfields()) {
        auto position = sf::Vector2f{ 0.f, 0.f };
        pf.reset();
        if (player < player_count) {
            pf = playfield::create(res_manager, position);
            AddEntity(pf);
            position.x += pf_margin;
            player++;
        }
    }
}

void GameController::HandleEvent(const sf::Event& event)
{
    for (auto&& entity : mModel->GetEntities()) {
        if (entityHandleEvent(entity, shared_from_this(), event)) {
            break;
        }
    }
}

void GameController::Update(const float update_delta_seconds)
{
    mModel->ClearDrawableObjects();
    for (auto&& entity : mModel->GetEntities()) {
        entityUpdate(entity, update_delta_seconds, shared_from_this());
    }

}
#if 0 // TODO: reimplement Build Mode
void GameController::EnableBuildMode([[maybe_unused]]Location::LocationType type)
{
    // mBuildGhost->SetType(type);
    // bBuildModeEnabled = true;
}
#endif

#if 0 // TODO: Reimplement markers (again)
void GameController::RemoveMarker(ExpansionMarker::Ptr marker)
{
    mModel->RemoveEntity(marker);
}
#endif

} // namespace OpenLabora
