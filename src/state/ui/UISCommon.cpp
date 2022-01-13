#include <cassert>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "state/State.hpp"
#include "state/ui/UISCommon.hpp"
#include "state/gs/GSCommon.hpp"

UISCommon::UISCommon(std::shared_ptr<State> state,
                             const sf::VideoMode& vm)
    : UiState { state, vm }
{
    float col_width = mVideoMode.width / 3.f;
    float screen_center_y = mVideoMode.height / 2.f;
    float btn_height = 40.f;
    float total_height = btn_height;

    auto quit_btn = sfg::Button::Create("Quit");

    quit_btn->GetSignal(sfg::Widget::OnLeftClick).Connect(
    [state = this->mState]
    {
        assert(!state.expired());
        state.lock()->SetNextState<AppStateDefs::FinalState>();
    });

    auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    box->Show(false);

    box->Pack(quit_btn, true);

    box->SetAllocation(sf::FloatRect(col_width,
                                     screen_center_y - total_height / 2,
                                     col_width,
                                     total_height));

    mDesktop.Add(box);
    mMenuWidgets.push_back(box);
}

void UISCommon::HandleEventCommon(const sf::Event& evt)
{
    mDesktop.HandleEvent(evt);
    if ((evt.type == sf::Event::KeyPressed)
        && (evt.key.code == sf::Keyboard::Escape)) {
        for (auto& item : mMenuWidgets) {
            item->Show(bIsMenuHidden);
            assert(!mState.expired());
            auto& state = static_cast<GSCommon&>(mState.lock()->GetGameState());
            state.SetPaused(bIsMenuHidden);
            bIsMenuHidden = !bIsMenuHidden;
        }
    }
}

void UISCommon::HandleEvent(const sf::Event& evt)
{
    HandleEventCommon(evt);
}

void UISCommon::UpdateCommon(const float secondsSinceLastUpdate)
{
    mDesktop.Update(secondsSinceLastUpdate);
}

void UISCommon::Update(const float secondsSinceLastUpdate)
{
    UpdateCommon(secondsSinceLastUpdate);
}

bool UISCommon::DrawSelectPlotWindow(Plot::PlotType type,
                                     bool push_front,
                                     const sf::Vector2f position)
{
    auto window = sfg::Window::Create(sfg::Window::Style::NO_STYLE);
    auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

    if (type == Plot::PlotType::Central) {
        auto plot_btn1 = sfg::Button::Create("Plot 1");
        auto plot_btn2 = sfg::Button::Create("Plot 2");

        plot_btn1->GetSignal(sfg::Widget::OnLeftClick).Connect(
        [state_ptr = this->mState, position, push_front]
        {
            assert(!state_ptr.expired());
            auto&& state =
                static_cast<GSCommon&>(state_ptr.lock()->GetGameState());
            auto&& res_mgr = state_ptr.lock()->GetResourceManager();
            auto playfield = state.GetActivePlayerPlayfield();
            auto plot = Plot{ Plot::kCentralPlotTop, res_mgr };
            plot.SetPosition(position);
            if (push_front) {
                playfield->PushPlotFront(plot);
            } else {
                playfield->PushPlotBack(plot);
            }
            return true;
        });
    } else {
        return false;
    }
    window->Add(box);
    return false;
}
