#include "state/ui/UISMainMenu.hpp"

#include <cassert>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "state/State.hpp"
#include "state/AppStateDefs.hpp"
#include "IRenderer.hpp"

UISMainMenu::UISMainMenu(std::shared_ptr<State> state, const sf::VideoMode& vm) :
    UiState { state, vm }
{
    float col_width = mVideoMode.width / 3.f;
    float screen_center_y = mVideoMode.height / 2.f;
    float box_padding = 8.f;
    float btn_height = 40.f;
    float total_height = 2 * btn_height + box_padding;

    auto duel_btn = sfg::Button::Create("Duel");
    auto quit_btn = sfg::Button::Create("Quit");
    auto state_ptr = mState;

    duel_btn->GetSignal(sfg::Widget::OnLeftClick).Connect([state_ptr] ()
    {
        assert(!state_ptr.expired());
        state_ptr.lock()->SetNextState<AppStateDefs::DuelState>();
    });
    quit_btn->GetSignal(sfg::Widget::OnLeftClick).Connect([state_ptr] ()
    {
        assert(!state_ptr.expired());
        state_ptr.lock()->SetNextState<AppStateDefs::FinalState>();
    });

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, box_padding);

    box->Pack(duel_btn, true);
    box->Pack(quit_btn, true);

    box->SetAllocation(sf::FloatRect(col_width,
                                     screen_center_y - total_height / 2,
                                     col_width,
                                     total_height));

    mDesktop.Add(box);
}
