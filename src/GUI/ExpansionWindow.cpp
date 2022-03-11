#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>
#include "GUI/ExpansionWindow.hpp"

namespace OpenLabora
{

ExpansionWindow::ExpansionWindow(GameController::Ptr controller)
    : mController{ controller }
{
    using Box = sfg::Box;
    auto btn_hbox = Box::Create(Box::Orientation::HORIZONTAL);
    btn_hbox->Pack(mConfirmButton);
    btn_hbox->Pack(mDeclineButton);

    auto confirm_text = sfg::Label::Create(std::string{kConfirmWindowText});
    auto main_vbox = Box::Create(Box::Orientation::VERTICAL, 10.f);
    main_vbox->Pack(confirm_text);
    main_vbox->Pack(btn_hbox);

    mWindow->Add(main_vbox);
    mWindow->Show(false);
}

void ExpansionWindow::SetState(Plot::PlotType)
{
}

} // namespace OpenLabora
