#include "GameState/Views/GVMainMenu.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

GVMainMenu::GVMainMenu(PtrView<IApplication<StateIdsVariant>> app,
                       PtrView<tgui::GuiSFML> gui,
                       std::shared_ptr<GCMainMenu> controller,
                       PtrView<const Model> model)
    : mApp{ app }, mController{ controller }, mModel{ model }
{
    auto win_size = static_cast<sf::Vector2f>(mModel->GetWindowSize());
    auto col_width = win_size.x / 3;
    auto screen_center_y = win_size.y / 2;
    auto box_padding = 8.f;
    auto btn_height = 40.f;
    auto total_height = 2 * btn_height + box_padding;

    #if 0
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
    #endif
};

void GVMainMenu::HandleEvent(const sf::Event& evt)
{
    if (evt.type == sf::Event::Resized) {
        HandleWindowResize({ evt.size.width, evt.size.height });
    }
};

void GVMainMenu::Update([[maybe_unused]]const float update_delta_seconds)
{
}

void GVMainMenu::HandleWindowResize([[maybe_unused]]const sf::Vector2u& window_size)
{
    // TODO resizable interface
    // mController->HandleWindowResize(window_size);
}

} // namespace OpenLabora
