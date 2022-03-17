#ifndef EXPANSIONWINDOW_HPP_
#define EXPANSIONWINDOW_HPP_

#include "GameState/Controllers/GameController.hpp"
#include "Game/Plot.hpp"

namespace OpenLabora
{

// Window that handles purchasing of plots - confirmation or selection
class ExpansionWindow final
{
    static constexpr std::string_view kConfirmButtonLabel= "Confirm";
    static constexpr std::string_view kDeclineButtonLabel = "Cancel";
    static constexpr std::string_view kConfirmWindowText =
        "Are you sure want to buy this plot?";
    static constexpr std::string_view kSelectWindowText =
        "Select which plot you want to purchase";

    // TODO fix gui
    #if 0
    static constexpr char kWindowStyle = Window::Style::BACKGROUND |
                                         Window::Style::TITLEBAR |
                                         Window::Style::SHADOW |
                                         Window::Style::CLOSE;

    GameController::Ptr mController;

    Window::Ptr mWindow = CreateEventConsumingWidget<Window>(mController,
                                                             kWindowStyle);
    Button::Ptr mConfirmButton = CreateWidget<Button>(kConfirmButtonLabel);
    Button::Ptr mDeclineButton = CreateWidget<Button>(kDeclineButtonLabel);
    #endif

public:
    ExpansionWindow(GameController::Ptr);

    #if 0
    Window::Ptr GetWindow() { return mWindow; }

    Button::Ptr GetConfirmButton() { return mConfirmButton; }

    Button::Ptr GetDeclineButton() { return mDeclineButton; }

    void SetState(Plot::PlotType);

    void Show(bool show) { mWindow->Show(show); };
    #endif
};

} // namespace OpenLabora


#endif // EXPANSIONWINDOW_HPP_
