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

#include "GameState/DuelFwd.hpp"
#include "GameState/Duel.hpp"
#include "GameState/ViewToViewModelBinding.hpp"
#include "ApplicationState/ApplicationContext.hpp"
#include "IGameWindow.hpp"
#include "Resource/IResourceManager.hpp"
#include "LibTypedefs.hpp"

namespace open_labora
{

void stateUpdate(Duel& state, float update_delta_seconds)
{
    state.Update(update_delta_seconds);
}

void stateHandleInput(Duel& state, Input::PtrConst input)
{
    if (input->IsMouseMoving()) {
        auto mouse_position = input->GetMousePosition();
        auto&& window = state.GetWindow();
        auto&& model = state.GetModel();
        const auto world_pos = window->MapScreenToWorldCoords(mouse_position);
        model.SetWorldMousePosition(world_pos);
    }

    state.HandleInput(input);
}

DrawableRangeConst stateGetDrawableObjects(Duel& state)
{ return state.GetModel().GetDrawableObjects(); }

void state::changeState(state::Duel,
                        ApplicationContext::Ptr app,
                        IGameWindow::Ptr window,
                        IResourceManager::Ptr resource_mgr)
{
    auto setup = [] (open_labora::Duel::VVMBindings& bindings)
    {
        auto&& escape_menu = std::get<EscapeMenuBinding>(bindings).view_model;
        auto&& cam = std::get<CameraBinding>(bindings).view_model;

        auto lock_cam = [&cam] { cam.LockCameraMovement(); };
        auto unlock_cam = [&cam] { cam.UnlockCameraMovement(); };
        escape_menu.SetLockCameraMovementCallback(lock_cam);
        escape_menu.SetUnlockCameraMovementCallback(unlock_cam);
    };
    auto model = std::make_unique<Model>();
    app->ChangeState<open_labora::Duel>(window,
                                        resource_mgr,
                                        std::move(model),
                                        setup);
}

bool stateGetFlagIsFinal(const Duel&) noexcept
{ return false; }

} // namespace open_labora
