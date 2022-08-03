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

#include "GameState/MainMenu.hpp"
#include "GameState/MainMenuFwd.hpp"
#include "GameState/DuelFwd.hpp"
#include "GameState/FinalFwd.hpp"
#include "GUI/GuiTypedefs.hpp"

namespace open_labora
{

MainMenu::MainMenu(ApplicationContext::Ptr app,
                   IGameWindow::Ptr window,
                   std::shared_ptr<IResourceManager> resource_mgr)
    : mApp{ app },
      mWindow{ window }
{
    auto box_padding_ratio = 0.1f;

    auto vbox = VBox::create();
    vbox->setOrigin(0.5f, 0.5f);
    vbox->setPosition("50%", "50%");
    vbox->setSize("20%", "10%");

    auto duel_btn = Button::create("Duel");
    auto quit_btn = Button::create("Quit");

    auto start_main = [app = mApp, mWindow = mWindow, resource_mgr]
    { state::changeState<state::Duel>(app, mWindow, resource_mgr); };

    auto stop_app = [app = mApp] { state::changeState<state::Final>(app); };

    duel_btn->onPress(start_main);
    quit_btn->onPress(stop_app);

    vbox->add(duel_btn);
    vbox->addSpace(box_padding_ratio);
    vbox->add(quit_btn);

    mWindow->AddWidget(vbox);
}

void stateUpdate([[maybe_unused]]MainMenu& state,
                 [[maybe_unused]]float update_delta_seconds)
{
}

void stateHandleInput(MainMenu& state, Input::PtrConst input)
{
    if (input->IsButtonDown(input::Button::Escape)) {
        state::changeState<state::Final>(state.GetApp());
        return;
    }
}

DrawableRangeConst stateGetDrawableObjects(MainMenu&)
{ return {}; }

void state::changeState(state::MainMenu,
                        ApplicationContext::Ptr app,
                        IGameWindow::Ptr window,
                        std::shared_ptr<IResourceManager> resource_mgr)
{ app->ChangeState<open_labora::MainMenu>(window, resource_mgr); }

bool stateGetFlagIsFinal(const MainMenu&) noexcept
{ return false; }

} // namespace open_labora
