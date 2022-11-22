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

#ifndef CONFIRMATIONWINDOW_HPP_
#define CONFIRMATIONWINDOW_HPP_

#include "Misc/CommonTypedefs.hpp"
#include "LibTypedefs.hpp"
#include "GuiTypedefs.hpp"
#include "GUI/Common.hpp"
#include "IGameWindow.hpp"

namespace open_labora
{

class ConfirmationWindow final
{
    inline static const GuiString kConfirmButtonLabel{ "Confirm" };
    inline static const GuiString kDeclineButtonLabel{ "Cancel" };
    inline static const GuiString kWindowTitle{ "" };

    static constexpr uint kTitleBarButtons = TitleButtonStyle::None;
    static constexpr uint kButtonsGroupHeight = 30;

    Panel::Ptr mBlockingPanel = Panel::create();

    ChildWindow::Ptr mWindow;

    Button::Ptr mConfirmButton;
    Button::Ptr mDeclineButton;
    Group::Ptr mButtonsGroup = Group::create();

    Group::Ptr mContent = Group::create();

public:
    using ConfirmAction = std::function<void()>;
    using DeclineAction = std::function<void()>;
    using OnWindowCloseAction = std::function<void()>;
    using EnableConfirmButtonCallback = std::function<void()>;

    template<class TWidthLayout, class THeightLayout>
    ConfirmationWindow(IGameWindow::Ptr game_window,
                       TWidthLayout&& window_width,
                       THeightLayout&& window_height,
                       uint title_bar_style = kTitleBarButtons,
                       GuiString window_title = kWindowTitle,
                       GuiString confirm_button_text = kConfirmButtonLabel,
                       GuiString decline_button_text = kDeclineButtonLabel);

    void SetContent(Group::Ptr);

    EnableConfirmButtonCallback GetEnableConfirmButtonCallback() const noexcept
    { return [button = mConfirmButton] { button->setEnabled(true); }; }

    void SetConfirmButtonEnabled(bool enabled);

    bool IsConfirmButtonEnabled() const { return mConfirmButton->isEnabled(); }

    void SetConfirmButtonAction(ConfirmAction);

    void SetDeclineButtonAction(DeclineAction);

    void Confirm();

    void Decline();

    Vector2f GetWindowSize() const { return mWindow->getFullSize(); }

    // Sets window's close button action too
    void SetOnWindowCloseAction(OnWindowCloseAction);

    void Show(bool show = true);

    bool IsVisible() const { return mWindow->isVisible(); }
};

template<class TWidthLayout, class THeightLayout>
ConfirmationWindow::ConfirmationWindow(IGameWindow::Ptr game_window,
                                       TWidthLayout&& window_width,
                                       THeightLayout&& window_height,
                                       uint title_bar_style,
                                       GuiString window_title,
                                       GuiString confirm_button_text,
                                       GuiString decline_button_text)
    : mWindow{ ChildWindow::create(window_title, title_bar_style) },
      mConfirmButton{ Button::create(confirm_button_text) },
      mDeclineButton{ Button::create(decline_button_text) }
{
    mBlockingPanel->setInheritedOpacity(0.f);
    mBlockingPanel->setVisible(false);
    mWindow->setVisible(false);

    gui::setDynamicTextSize(mWindow, game_window, gui::getRegularTextSize);

    mWindow->setOrigin(0.5f, 0.5f);
    mWindow->setPosition("50%", "50%");
    mWindow->setSize(window_width, window_height);
    mWindow->add(mContent);

    game_window->AddWidget(mBlockingPanel);
    game_window->AddWidget(mWindow);

    mButtonsGroup->add(mConfirmButton);
    mButtonsGroup->add(mDeclineButton);

    auto button_width = (mWindow->getClientSize().x - 3 * gui::kMargin) / 2;
    mConfirmButton->setSize(button_width, kButtonsGroupHeight);
    mConfirmButton->setPosition(0, 0);

    const auto decline_x = tgui::bindRight(mConfirmButton) + gui::kMargin;
    mDeclineButton->setSize(button_width, kButtonsGroupHeight);
    mDeclineButton->setPosition(decline_x, 0);
}

} // namespace open_labora

#endif // CONFIRMATIONWINDOW_HPP_
