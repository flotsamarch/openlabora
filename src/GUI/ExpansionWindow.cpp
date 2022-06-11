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

namespace expansionWindow
{

using TextAlignment = tgui::Label::HorizontalAlignment;
constexpr auto vbox_padding_ratio = 3.f;
constexpr auto buttons_ratio = 30.f;
constexpr auto text_size = 18u;

void setState(const StateChooseOne&,
              tgui::ChildWindow::Ptr window,
              tgui::VerticalLayout::Ptr box,
              tgui::HorizontalLayout::Ptr buttons_hbox,
              tgui::Button::Ptr confirm_button)
{
    static const tgui::String select_text =
        "Select which plot you want to purchase";

    auto select_label = tgui::Label::create(select_text);
    select_label->setTextSize(text_size);
    select_label->setHorizontalAlignment(TextAlignment::Center);

    window->setSize("15%", "23%");
    constexpr auto toggle_ratio = 137.f;
    auto remaining_ratio = window->getClientSize().y;
    remaining_ratio -= buttons_ratio + toggle_ratio + 4 * vbox_padding_ratio;

    auto alt_toggle_1 = tgui::ToggleButton::create("1");
    auto alt_toggle_2 = tgui::ToggleButton::create("2");
    auto toggle_buttons_hbox = tgui::HorizontalLayout::create();

    auto button_on_toggle =
    [alt_toggle_1, alt_toggle_2, confirm_button]
    (tgui::ToggleButton::Ptr other)
    {
        other->setDown(false);
        if (alt_toggle_1->isDown() || alt_toggle_2->isDown()) {
            confirm_button->setEnabled(true);
            return;
        }
        confirm_button->setEnabled(false);
    };

    toggle_buttons_hbox->addSpace(kHBoxMarginRatio);
    toggle_buttons_hbox->add(alt_toggle_1, kAltToggle1Name);
    toggle_buttons_hbox->addSpace(kHBoxMarginRatio);
    toggle_buttons_hbox->add(alt_toggle_2, kAltToggle2Name);
    toggle_buttons_hbox->addSpace(kHBoxMarginRatio);
    alt_toggle_1->onClick(button_on_toggle, alt_toggle_2);
    alt_toggle_2->onClick(button_on_toggle, alt_toggle_1);

    box->addSpace(vbox_padding_ratio);
    box->add(select_label, remaining_ratio);
    box->addSpace(vbox_padding_ratio);
    box->add(toggle_buttons_hbox, toggle_ratio);
    box->addSpace(vbox_padding_ratio);
    box->add(buttons_hbox, buttons_ratio);
    box->addSpace(vbox_padding_ratio);

    confirm_button->setEnabled(false);
    alt_toggle_1->setDown(false);
    alt_toggle_2->setDown(false);
}

void setState(const StateConfirm&,
              tgui::ChildWindow::Ptr window,
              tgui::VerticalLayout::Ptr box,
              tgui::HorizontalLayout::Ptr buttons_hbox,
              tgui::Button::Ptr confirm_button)
{
    static const tgui::String confirm_text =
        "Are you sure want to buy this plot?";

    auto confirm_label = tgui::Label::create(confirm_text);
    confirm_label->setTextSize(text_size);
    confirm_label->setHorizontalAlignment(TextAlignment::Center);

    window->setSize("15%", "10%");
    auto remaining_ratio = window->getClientSize().y;
    remaining_ratio -= buttons_ratio + 3 * vbox_padding_ratio;

    box->addSpace(vbox_padding_ratio);
    box->add(confirm_label, remaining_ratio);
    box->addSpace(vbox_padding_ratio);
    box->add(buttons_hbox, buttons_ratio);
    box->addSpace(vbox_padding_ratio);

    confirm_button->setEnabled(true);
}

}

uint32_t ExpansionWindow::GetToggleValue() const
{
    const auto& alt_toggle_name_1 = expansionWindow::kAltToggle1Name;
    const auto& alt_toggle_name_2 = expansionWindow::kAltToggle2Name;

    auto alt_toggle_1 = mMainVBox->get<tgui::ToggleButton>(alt_toggle_name_1);
    auto alt_toggle_2 = mMainVBox->get<tgui::ToggleButton>(alt_toggle_name_2);

    if (alt_toggle_1 == nullptr || alt_toggle_2 == nullptr) {
        return 0;
    }

    const bool alt1_toggled = alt_toggle_1->isDown();
    const bool alt2_toggled = alt_toggle_2->isDown();

    if (!alt1_toggled && !alt2_toggled) {
        return 0;
    }
    return alt1_toggled ? 1 : 2;
}

void ExpansionWindow::Show(bool show)
{
    mBlockingPanel->setVisible(show);
    mWindow->setVisible(show);
};

} // namespace OpenLabora
