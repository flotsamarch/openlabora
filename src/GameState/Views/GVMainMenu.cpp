#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "AppState/AppStateManager.hpp"
#include "GameState/Views/GVMainMenu.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

GVMainMenu::GVMainMenu(std::shared_ptr<AppStateManager> state,
                       std::shared_ptr<IGameController> controller,
                       std::shared_ptr<const Model> model)
    : mState{ state }, mController{ controller }, mModel{ model }
{
    float col_width = mModel->mWindowSize.x / 3.f;
    float screen_center_y = mModel->mWindowSize.y / 2.f;
    float box_padding = 8.f;
    float btn_height = 40.f;
    float total_height = 2 * btn_height + box_padding;

    auto duel_btn = sfg::Button::Create("Duel");
    auto quit_btn = sfg::Button::Create("Quit");

    duel_btn->GetSignal(sfg::Widget::OnLeftClick).Connect(
    [state_ptr = this->mState]
    {
        assert(!state_ptr.expired());
        state_ptr.lock()->SetNextState<AppStateDefs::DuelState>();
    });

    quit_btn->GetSignal(sfg::Widget::OnLeftClick).Connect(
    [state_ptr = this->mState]
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
};

GVMainMenu::~GVMainMenu() noexcept
{
    mDesktop.RemoveAll();
    mDesktop.Refresh();
};

void GVMainMenu::HandleEvent(const sf::Event& evt)
{
    mDesktop.HandleEvent(evt);

    if (evt.type == sf::Event::Resized) {
        HandleWindowResize({ evt.size.width, evt.size.height });
    }
};

void GVMainMenu::Update(const float update_delta_seconds)
{
    mDesktop.Update(update_delta_seconds);
}

void GVMainMenu::HandleWindowResize([[maybe_unused]]const sf::Vector2u& window_size)
{
    // TODO resizable interface
    // mController->HandleWindowResize(window_size);
}

} // namespace OpenLabora
