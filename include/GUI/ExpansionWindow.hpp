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
#include <string>
#include "GameState/Controllers/GameController.hpp"
#include "Game/Plot.hpp"

namespace OpenLabora
{

// Window that handles purchasing of plots - confirmation or selection
class ExpansionWindow final
{
    inline static const tgui::String kConfirmButtonLabel= "Confirm";
    inline static const tgui::String kDeclineButtonLabel = "Cancel";
    inline static const tgui::String kConfirmWindowText =
        "Are you sure want to buy this plot?";
    inline static const tgui::String kSelectWindowText =
        "Select which plot you want to purchase";
    inline static const tgui::String kWindowTitle = "";

    static constexpr unsigned int kTitleBarButtons = 0u;

    using Window = tgui::ChildWindow;
    using Button = tgui::Button;
    using ToggleButton = tgui::ToggleButton;
    using HBox = tgui::HorizontalLayout;
    using VBox = tgui::VerticalLayout;
    using Label = tgui::Label;

    GameController::Ptr mController;

    Window::Ptr mWindow = Window::create(kWindowTitle, kTitleBarButtons);
    Button::Ptr mConfirmButton = Button::create(kConfirmButtonLabel);
    Button::Ptr mDeclineButton = Button::create(kDeclineButtonLabel);
    ToggleButton::Ptr mAltToggle1 = ToggleButton::create("1");
    ToggleButton::Ptr mAltToggle2 = ToggleButton::create("2");

    Label::Ptr mConfirmText = Label::create(kConfirmWindowText);
    Label::Ptr mSelectText = Label::create(kSelectWindowText);

    HBox::Ptr mAcceptDeclineHBox = HBox::create();
    HBox::Ptr mToggleButtonsHBox = HBox::create();
    VBox::Ptr mMainVBox = VBox::create();

public:
    ExpansionWindow(GameController::Ptr);

    Window::Ptr GetWindow() { return mWindow; }

    Button::Ptr GetConfirmButton() { return mConfirmButton; }

    Button::Ptr GetDeclineButton() { return mDeclineButton; }

    void SetState(Plot::PlotType);

    void Show(bool show) { mWindow->setVisible(show); };

    // Callback for ToggleButtons
    // @arg other - Other toggle button to be untoggled;
    void ButtonOnToggle(ToggleButton::Ptr other);

    uint32_t GetToggleValue() const;
};

} // namespace OpenLabora


#endif // EXPANSIONWINDOW_HPP_
