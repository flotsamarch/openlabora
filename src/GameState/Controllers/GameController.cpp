// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

GameController::GameController(PtrView<IApplication<StateIdsVariant>> app,
                               IResourceManager::Ptr resource_mgr,
                               Model::Ptr model,
                               uint32_t player_count)
    : mApp{ app }, mModel{ model }, mResourceMgr{ resource_mgr }
{
    auto pf_width = static_cast<float>(playfield::kMaxFieldWidth);
    auto pf_margin = pf_width * tile::kTileWidth + 3 * tile::kTileWidth;

    for (uint32_t player{0}; auto&& pf : mModel->GetPlayfields()) {
        auto position = sf::Vector2f{ 0.f, 0.f };
        pf.reset();
        if (player < player_count) {
            pf = playfield::create(resource_mgr, position);
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
        entityUpdate(entity, shared_from_this(), update_delta_seconds);
    }

}

#if 0 // TODO: reimplement Build Mode
void GameController::EnableBuildMode([[maybe_unused]]Location::LocationType type)
{
    // mBuildGhost->SetType(type);
    // bBuildModeEnabled = true;
}
#endif

} // namespace OpenLabora
