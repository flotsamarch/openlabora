#ifndef EXPANSIONWINDOW_HPP_
#define EXPANSIONWINDOW_HPP_

#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>
#include <TGUI/Widgets/Button.hpp>
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

    GameController::Ptr mController;

    Window::Ptr mWindow = Window::create(kWindowTitle, kTitleBarButtons);
    Button::Ptr mConfirmButton = Button::create(kConfirmButtonLabel);
    Button::Ptr mDeclineButton = Button::create(kDeclineButtonLabel);

public:
    ExpansionWindow(GameController::Ptr);

    Window::Ptr GetWindow() { return mWindow; }

    Button::Ptr GetConfirmButton() { return mConfirmButton; }

    Button::Ptr GetDeclineButton() { return mDeclineButton; }

    void SetState(Plot::PlotType);

    void Show(bool show) { mWindow->setVisible(show); };
};

} // namespace OpenLabora


#endif // EXPANSIONWINDOW_HPP_
