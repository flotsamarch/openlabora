#include "GameState/Controllers/GameController.hpp"
#include "AppState/AppStateManager.hpp"
#include "Game/ExpansionMarker.hpp"

namespace OpenLabora
{

GameController::GameController(std::shared_ptr<AppStateManager> state,
                               std::shared_ptr<Model> model,
                               unsigned int player_count)
    : mState{ state }, mModel{ model }
{
    using PT = Plot::PlotType;
    auto&& res_mgr = state->GetResourceManager();
    mModel->mEntities.clear();
    mModel->mSelectableEntities.clear();

    for (unsigned int player{0}; auto&& pf : mModel->mPlayfields) {
        pf.reset();
        if (player < player_count) {
            pf = CreateEntity<Playfield>(res_mgr);
        }
    }

    auto [top_marker_pos, btm_marker_pos] =
        GetActivePlayerPlayfield()->GetExpansionMarkerPositions(PT::Central);

    auto marker_central_top = CreateEntity<ExpansionMarker>(
        Plot{Plot::kCentralPlotTop, res_mgr}, true);
    auto marker_central_bottom = CreateEntity<ExpansionMarker>(
        Plot{Plot::kCentralPlotBottom, res_mgr}, false);

    marker_central_top->SetPosition(top_marker_pos);
    marker_central_bottom->SetPosition(btm_marker_pos);
    // TODO initialize mModel->mBuildGhost something...something...
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
