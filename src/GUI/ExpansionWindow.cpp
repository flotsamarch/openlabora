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

#include "GUI/ExpansionWindow.hpp"

namespace OpenLabora
{

ExpansionWindow::ExpansionWindow(GameController::Ptr controller)
    : mController{ controller }
{
    using TextAlignment = tgui::Label::HorizontalAlignment;
    const auto hbox_margin_ratio = 0.03f;
    const auto text_size = 18u;

    mWindow->setOrigin(0.5f, 0.5f);
    mWindow->setPosition("50%", "50%");

    mConfirmText->setTextSize(text_size);
    mConfirmText->setHorizontalAlignment(TextAlignment::Center);
    mSelectText->setTextSize(text_size);
    mSelectText->setHorizontalAlignment(TextAlignment::Center);

    mToggleButtonsHBox->addSpace(hbox_margin_ratio);
    mToggleButtonsHBox->add(mAltToggle1);
    mToggleButtonsHBox->addSpace(hbox_margin_ratio);
    mToggleButtonsHBox->add(mAltToggle2);
    mToggleButtonsHBox->addSpace(hbox_margin_ratio);

    mAcceptDeclineHBox->addSpace(hbox_margin_ratio);
    mAcceptDeclineHBox->add(mConfirmButton);
    mAcceptDeclineHBox->addSpace(hbox_margin_ratio);
    mAcceptDeclineHBox->add(mDeclineButton);
    mAcceptDeclineHBox->addSpace(hbox_margin_ratio);

    mAltToggle1->onClick(&ExpansionWindow::ButtonOnToggle, this, mAltToggle2);
    mAltToggle2->onClick(&ExpansionWindow::ButtonOnToggle, this, mAltToggle1);

    mWindow->add(mMainVBox);
    mWindow->setVisible(false);
}

void ExpansionWindow::SetState(plot::Type type)
{
    const auto vbox_padding_ratio = 3.f;
    const auto buttons_ratio = 30.f;

    mMainVBox->removeAllWidgets();

    if (type != plot::Type::Central) {
        mWindow->setSize("15%", "10%");
        auto remaining_ratio = mWindow->getClientSize().y;
        remaining_ratio -= buttons_ratio + 3 * vbox_padding_ratio;

        mMainVBox->addSpace(vbox_padding_ratio);
        mMainVBox->add(mConfirmText, remaining_ratio);
        mMainVBox->addSpace(vbox_padding_ratio);
        mMainVBox->add(mAcceptDeclineHBox, buttons_ratio);
        mMainVBox->addSpace(vbox_padding_ratio);

        mConfirmButton->setEnabled(true);
    } else {
        mWindow->setSize("15%", "23%");
        const auto toggle_ratio = 137.f;
        auto remaining_ratio = mWindow->getClientSize().y;
        remaining_ratio -= buttons_ratio + toggle_ratio + 4 * vbox_padding_ratio;

        mMainVBox->addSpace(vbox_padding_ratio);
        mMainVBox->add(mSelectText, remaining_ratio);
        mMainVBox->addSpace(vbox_padding_ratio);
        mMainVBox->add(mToggleButtonsHBox, toggle_ratio);
        mMainVBox->addSpace(vbox_padding_ratio);
        mMainVBox->add(mAcceptDeclineHBox, buttons_ratio);
        mMainVBox->addSpace(vbox_padding_ratio);

        mConfirmButton->setEnabled(false);
        mAltToggle1->setDown(false);
        mAltToggle2->setDown(false);
    }
}

void ExpansionWindow::ButtonOnToggle(ToggleButton::Ptr other)
{
    other->setDown(false);
    if (mAltToggle1->isDown() || mAltToggle2->isDown()) {
        mConfirmButton->setEnabled(true);
        return;
    }
    mConfirmButton->setEnabled(false);
}

uint32_t ExpansionWindow::GetToggleValue() const
{
    const bool alt1_toggled = mAltToggle1->isDown();
    const bool alt2_toggled = mAltToggle2->isDown();

    if (!alt1_toggled && !alt2_toggled) {
        return 0;
    }
    return alt1_toggled ? 1 : 2;
}

} // namespace OpenLabora
