#ifndef EXPANSIONWINDOW_HPP_
#define EXPANSIONWINDOW_HPP_

#include <SFGUI/Desktop.hpp>
#include <SFGUI/Widget.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include "GameState/Controllers/GameController.hpp"
#include "GUI/Utility.hpp"
#include "Game/Plot.hpp"

namespace OpenLabora
{

// Window that handles purchasing of plots - confirmation or selection
class ExpansionWindow final
{
    using Window = sfg::Window;
    using Widget = sfg::Widget;
    using Button = sfg::Button;
    using ToggleButton = sfg::ToggleButton;

    static constexpr std::string_view kConfirmButtonLabel= "Confirm";
    static constexpr std::string_view kDeclineButtonLabel = "Cancel";
    static constexpr std::string_view kConfirmWindowText =
        "Are you sure want to buy this plot?";
    static constexpr std::string_view kSelectWindowText =
        "Select which plot you want to purchase";

    static constexpr char kWindowStyle = Window::Style::BACKGROUND |
                                         Window::Style::TITLEBAR |
                                         Window::Style::SHADOW |
                                         Window::Style::CLOSE;

    GameController::Ptr mController;

    Window::Ptr mWindow = CreateEventConsumingWidget<Window>(mController,
                                                             kWindowStyle);
    Button::Ptr mConfirmButton = CreateWidget<Button>(kConfirmButtonLabel);
    Button::Ptr mDeclineButton = CreateWidget<Button>(kDeclineButtonLabel);


    // Create labelled widgets which are visible during gameplay
    template<CWidget TWidget>
    typename TWidget::Ptr CreateWidget(const std::string_view& label);

public:
    ExpansionWindow(GameController::Ptr);

    Window::Ptr GetWindow() { return mWindow; }

    Button::Ptr GetConfirmButton() { return mConfirmButton; }

    Button::Ptr GetDeclineButton() { return mDeclineButton; }

    void SetState(Plot::PlotType);

    void Show(bool show) { mWindow->Show(show); };
};

template<CWidget TWidget>
typename TWidget::Ptr
ExpansionWindow::CreateWidget(const std::string_view& label)
{
    return CreateEventConsumingWidget<TWidget>(mController, std::string{label});
}

} // namespace OpenLabora


#endif // EXPANSIONWINDOW_HPP_
