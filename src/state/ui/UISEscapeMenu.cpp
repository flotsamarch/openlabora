#include "state/ui/UISEscapeMenu.hpp"

#include <cassert>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "state/State.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"

UISEscapeMenu::UISEscapeMenu(std::shared_ptr<State> state) : UiState { state }
{
    auto video_mode = GetRenderer().GetVideoMode();
    float col_width = video_mode.width / 3.f;
    float screen_center_y = video_mode.height / 2.f;
    float btn_height = 40.f;
    float total_height = btn_height;

    auto quit_btn = sfg::Button::Create("Quit");
    auto state_ptr = mState;

    quit_btn->GetSignal(sfg::Widget::OnLeftClick).Connect([state_ptr]{
        assert(!state_ptr.expired());
        state_ptr.lock()->ChangeState<AppStateDefs::FinalState>();
        });

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    box->Show(false);

    box->Pack(quit_btn, true);

    box->SetAllocation(sf::FloatRect(col_width,
                                     screen_center_y - total_height / 2,
                                     col_width,
                                     total_height));

    AddWidgetToDesktop(box);
    mMenuWidgets.push_back(box);
}

void UISEscapeMenu::HandleEvent(const sf::Event& evt)
{
    if ((evt.type == sf::Event::KeyPressed)
        && (evt.key.code == sf::Keyboard::Escape)) {
        for (auto& item : mMenuWidgets) {
            item->Show(bIsMenuHidden);
            bIsMenuHidden = !bIsMenuHidden;
        }
    }
}
