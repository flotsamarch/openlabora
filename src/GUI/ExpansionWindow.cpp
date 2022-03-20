#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>
#include <TGUI/Widgets/Label.hpp>
#include "GUI/ExpansionWindow.hpp"

namespace OpenLabora
{

ExpansionWindow::ExpansionWindow(GameController::Ptr controller)
    : mController{ controller }
{
    using TextAlignment = tgui::Label::HorizontalAlignment;
    using HBox = tgui::HorizontalLayout;
    using VBox = tgui::VerticalLayout;
    const auto vbox_margin_ratio = 0.07f;
    const auto hbox_margin_ratio = 0.03f;
    const auto buttons_size_ratio = 0.4f;
    const auto text_size = 18u;

    mWindow->setOrigin(0.5f, 0.5f);
    mWindow->setPosition("50%", "50%");
    mWindow->setSize("15%", "10%");

    auto btn_hbox = HBox::create();
    btn_hbox->addSpace(hbox_margin_ratio);
    btn_hbox->add(mConfirmButton);
    btn_hbox->addSpace(hbox_margin_ratio);
    btn_hbox->add(mDeclineButton);
    btn_hbox->addSpace(hbox_margin_ratio);

    auto confirm_text = tgui::Label::create(kConfirmWindowText);
    confirm_text->setTextSize(text_size);
    confirm_text->setHorizontalAlignment(TextAlignment::Center);

    auto text_hbox = HBox::create();
    text_hbox->addSpace(hbox_margin_ratio);
    text_hbox->add(confirm_text);
    text_hbox->addSpace(hbox_margin_ratio);

    auto main_vbox = VBox::create();
    main_vbox->addSpace(vbox_margin_ratio);
    main_vbox->add(text_hbox);
    main_vbox->addSpace(vbox_margin_ratio);
    main_vbox->add(btn_hbox, buttons_size_ratio);
    main_vbox->addSpace(vbox_margin_ratio);

    mWindow->add(main_vbox);
    mWindow->setVisible(false);
}

void ExpansionWindow::SetState(Plot::PlotType)
{
}

} // namespace OpenLabora
