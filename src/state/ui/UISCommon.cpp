#include <cassert>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "state/State.hpp"
#include "state/ui/UISCommon.hpp"
#include "state/gs/GSCommon.hpp"

UISCommon::UISCommon(std::shared_ptr<State> state,
                             const sf::VideoMode& vm)
    : UISEscapeMenu { state, vm }
{
}

void UISCommon::HandleEventCommon(const sf::Event& evt)
{
    UISEscapeMenu::HandleEvent(evt);
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
    auto&& state_ptr = mState;

    if (type == Plot::PlotType::Central) {
        auto plot_btn1 = sfg::Button::Create("Plot 1");
        auto plot_btn2 = sfg::Button::Create("Plot 2");

        plot_btn1->GetSignal( sfg::Widget::OnLeftClick ).Connect(
            [state_ptr, position, push_front]{
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
