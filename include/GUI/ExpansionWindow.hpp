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

#ifndef EXPANSIONWINDOW_HPP_
#define EXPANSIONWINDOW_HPP_

#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/ToggleButton.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <string>
#include "GameWindow.hpp"

namespace OpenLabora
{

namespace expansionWindow {

struct StateChooseOne{};
struct StateConfirm{};
constexpr auto kHBoxMarginRatio = 0.03f;

inline const tgui::String kAltToggle1Name = "alt_toggle_1";
inline const tgui::String kAltToggle2Name = "alt_toggle_2";

void setState(const StateChooseOne&,
              tgui::ChildWindow::Ptr window,
              tgui::VerticalLayout::Ptr box,
              tgui::HorizontalLayout::Ptr buttons_hbox,
              tgui::Button::Ptr confirm_button);

void setState(const StateConfirm&,
              tgui::ChildWindow::Ptr window,
              tgui::VerticalLayout::Ptr box,
              tgui::HorizontalLayout::Ptr buttons_hbox,
              tgui::Button::Ptr confirm_button);

}

// Window that handles purchasing of plots - confirmation or selection
class ExpansionWindow final
{
    inline static const tgui::String kConfirmButtonLabel= "Confirm";
    inline static const tgui::String kDeclineButtonLabel = "Cancel";
    inline static const tgui::String kWindowTitle = "";

    static constexpr unsigned int kTitleBarButtons = 0u;

    using Window = tgui::ChildWindow;
    using Panel = tgui::Panel;
    using Button = tgui::Button;
    using HBox = tgui::HorizontalLayout;
    using VBox = tgui::VerticalLayout;

    Panel::Ptr mBlockingPanel = Panel::create();
    Window::Ptr mWindow = Window::create(kWindowTitle, kTitleBarButtons);
    Button::Ptr mConfirmButton = Button::create(kConfirmButtonLabel);
    Button::Ptr mDeclineButton = Button::create(kDeclineButtonLabel);

    HBox::Ptr mAcceptDeclineHBox = HBox::create();
    VBox::Ptr mMainVBox = VBox::create();

public:
    template<class TGui, class TWindow>
    ExpansionWindow(GameWindow<TGui, TWindow>);

    Window::Ptr GetWindow() { return mWindow; }

    Button::Ptr GetConfirmButton() { return mConfirmButton; }

    Button::Ptr GetDeclineButton() { return mDeclineButton; }

    void SetState(const auto& state);

    void Show(bool show);

    uint32_t GetToggleValue() const;
};

template<class TGui, class TWindow>
ExpansionWindow::ExpansionWindow(GameWindow<TGui, TWindow> game_window)
{
    mBlockingPanel->setInheritedOpacity(0.f);

    mWindow->setOrigin(0.5f, 0.5f);
    mWindow->setPosition("50%", "50%");

    mAcceptDeclineHBox->addSpace(expansionWindow::kHBoxMarginRatio);
    mAcceptDeclineHBox->add(mConfirmButton);
    mAcceptDeclineHBox->addSpace(expansionWindow::kHBoxMarginRatio);
    mAcceptDeclineHBox->add(mDeclineButton);
    mAcceptDeclineHBox->addSpace(expansionWindow::kHBoxMarginRatio);

    mWindow->add(mMainVBox);
    mWindow->setVisible(false);
    mBlockingPanel->setVisible(false);

    game_window.AddWidget(mBlockingPanel);
    game_window.AddWidget(mWindow);
}

void ExpansionWindow::SetState(const auto& state) {
    mMainVBox->removeAllWidgets();
    expansionWindow::setState(state,
                              mWindow,
                              mMainVBox,
                              mAcceptDeclineHBox,
                              mConfirmButton);
}


} // namespace OpenLabora


#endif // EXPANSIONWINDOW_HPP_
