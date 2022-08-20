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

#ifndef ESCAPEMENUVIEW_HPP_
#define ESCAPEMENUVIEW_HPP_

#include "ApplicationState/ApplicationContext.hpp"
#include "IGameWindow.hpp"
#include "GUI/GuiTypedefs.hpp"
#include "GameState/FinalFwd.hpp"
#include "Input/Input.hpp"

namespace open_labora
{

template<class TViewModel>
class EscapeMenuView final
{
    ApplicationContext::Ptr mApp;
    IGameWindow::Ptr mGameWindow;
    PtrView<TViewModel> mViewModel;

    VBox::Ptr menu_vbox = VBox::create();

public:
    EscapeMenuView(ApplicationContext::Ptr,
                   IGameWindow::Ptr,
                   PtrView<TViewModel>);

    bool HandleInput(Input::PtrConst);

    void Update([[maybe_unused]]float update_delta_seconds)
    {
    }
};

template<class TViewModel>
EscapeMenuView<TViewModel>
::EscapeMenuView(ApplicationContext::Ptr app,
                 IGameWindow::Ptr game_window,
                 PtrView<TViewModel> view_model)
    : mApp{ app },
      mGameWindow{ game_window },
      mViewModel{ view_model }
{
    auto quit_btn = Button::create("Quit");
    auto resume_btn = Button::create("Resume");

    quit_btn->onPress([app = mApp] { state::changeState<state::Final>(app); });
    resume_btn->onPress([box = menu_vbox] { box->setVisible(false); });

    menu_vbox->setVisible(false);
    menu_vbox->add(quit_btn, true);
    menu_vbox->addSpace(0.1f);
    menu_vbox->add(resume_btn, true);
    menu_vbox->setOrigin(0.5f, 0.5f);
    menu_vbox->setPosition("50%", "50%");
    menu_vbox->setSize("20%", "10%");

    mGameWindow->AddWidget(menu_vbox);
};

template<class TViewModel>
bool EscapeMenuView<TViewModel>
::HandleInput(Input::PtrConst input)
{
    if (input->HasButtonBeenPressed(input::Button::Escape)) {
        const bool is_visible = menu_vbox->isVisible();
        menu_vbox->setVisible(!is_visible);
        mViewModel->SetOpen(!is_visible);
        return true;
    }
    return false;
};

} // namespace open_labora

#endif // ESCAPEMENUVIEW_HPP_
