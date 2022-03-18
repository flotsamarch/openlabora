#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

GameController::GameController(PtrView<IApplication<StateIdsVariant>> app,
                               IResourceManager::Ptr res_manager,
                               Model::Ptr model,
                               uint32_t player_count)
    : mApp { app }, mResManager{ res_manager }, mModel{ model }
{
    mModel->ResetEntities();

    auto pf_width = static_cast<float>(Playfield::kMaxFieldWidth);
    auto pf_margin = pf_width * Tile::kTileWidth + 3 * Tile::kTileWidth;
    for (uint32_t player{0}; auto&& pf : mModel->GetPlayfields()) {
        auto position = sf::Vector2f{ 0.f, 0.f };
        pf.reset();
        if (player < player_count) {
            pf = mModel->CreateEntity<Playfield>(mResManager);
            pf->SetPosition(position);
            player++;
            position.x += pf_margin;
        }
    }
}

    void GameController::HandleEvent([[maybe_unused]]const sf::Event& evt)
{
    // TODO Ignore events
    #if 0
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
    #endif
}

void GameController::HandleWindowResize(const sf::Vector2u&)
{
    // mModel->SetWindowSize(window_size);
}

void GameController::Update([[maybe_unused]]const float update_delta_seconds) {}

void GameController::EnableBuildMode([[maybe_unused]]Location::LocationType type)
{
    // TODO fix build mode
    // mBuildGhost->SetType(type);
    // bBuildModeEnabled = true;
}

void GameController::RemoveMarker(ExpansionMarker::Ptr marker)
{
    mModel->RemoveEntity(marker);
}

} // namespace OpenLabora
