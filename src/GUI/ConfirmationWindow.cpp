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

#include "GUI/ConfirmationWindow.hpp"

namespace open_labora
{

void ConfirmationWindow::SetContent(Group::Ptr content)
{
    mContent->removeAllWidgets();
    mContent->add(content);

    const auto available_height = mWindow->getClientSize().y - 3 * gui::kMargin;
    const auto content_height = available_height - kButtonsGroupHeight;

    content->setPosition(gui::kMargin, gui::kMargin);
    content->setSize("100%", content_height);

    const auto buttons_pos = bindBottom(content) + gui::kMargin;
    mContent->add(mButtonsGroup);
    mButtonsGroup->setSize("100%", kButtonsGroupHeight);
    mButtonsGroup->setPosition(gui::kMargin, buttons_pos);
}

void ConfirmationWindow::SetConfirmButtonEnabled(bool enabled)
{
    mConfirmButton->setEnabled(enabled);
}

void ConfirmationWindow::SetConfirmButtonAction(std::function<void()> action)
{
    mConfirmButton->onMouseRelease.connect(action);
}

void ConfirmationWindow::SetDeclineButtonAction(std::function<void()> action)
{
    mDeclineButton->onMouseRelease.connect(action);
}

void ConfirmationWindow::Confirm()
{
    mConfirmButton->onMouseRelease.emit(mConfirmButton.get(), {});
}

void ConfirmationWindow::Decline()
{
    mDeclineButton->onMouseRelease.emit(mDeclineButton.get(), {});
}

void ConfirmationWindow::SetOnWindowCloseAction(std::function<void()> action)
{
    mWindow->onClose(action);
}

void ConfirmationWindow::Show(bool show)
{
    mWindow->setVisible(show);
    mBlockingPanel->setVisible(show);
    mWindow->setFocused(show);
}

} // namespace open_labora
