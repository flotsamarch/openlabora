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

    // Escape menu UI
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

    // Plot selection UI
    auto style = sfg::Window::Style::BACKGROUND | sfg::Window::Style::CLOSE
        | sfg::Window::Style::RESIZE;
    mCentralPlotSelectionWindow = sfg::Window::Create(style);

    auto central_sel_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

    auto central_plot_btn1 = sfg::Button::Create("Plot 1");
    auto central_plot_btn2 = sfg::Button::Create("Plot 2");

    using PT = Plot::PlotType;

    // This lambda creates a lamda that could be passed into button.connect()
    // method. We need this to avoid code duplication for multiple buttons
    // which behavior differs in only one line that creates different kind of
    // plot and because we cannot pass lambda with arguments into
    // button.connect() method
    auto create_plot = [state_ptr = this->mState,
                        &push_front = bExtendUpwards,
                        window = mCentralPlotSelectionWindow,
                        &hidden = this->bIsCentralPlotSelectionHidden]
        (const Plot::PlotTilesAndType& ptat)
    {
        return [state_ptr, &push_front, window, &hidden, &ptat]
            {
                assert(!state_ptr.expired());
                auto&& state =
                    static_cast<GSCommon&>(state_ptr.lock()->GetGameState());
                auto&& res_mgr = state_ptr.lock()->GetResourceManager();

                auto playfield = state.GetActivePlayerPlayfield();
                auto[top, bottom] =
                    playfield->GetLandTopAndBottomEdges(PT::Central);
                auto plot = Plot{ ptat, res_mgr };
                auto position = playfield->GetPosition();
                position.x +=
                    Plot::GetPlotWidthTileCount(PT::Coastal) * Tile::kTileWidth;

                if (push_front) {
                    position.y = top - Tile::kTileHeight;
                    plot.SetPosition(position);
                    playfield->PushPlotFront(plot);
                } else {
                    position.y = bottom;
                    plot.SetPosition(position);
                    playfield->PushPlotBack(plot);
                }
                hidden = true;
        };
    };

    central_plot_btn1->GetSignal(sfg::Widget::OnLeftClick)
        .Connect(create_plot(Plot::kCentralPlotTop));
    central_plot_btn2->GetSignal(sfg::Widget::OnLeftClick)
        .Connect(create_plot(Plot::kCentralPlotBottom));

    central_sel_box->Pack(central_plot_btn1);
    central_sel_box->Pack(central_plot_btn2);

    mCentralPlotSelectionWindow->Add(central_sel_box);
    mCentralPlotSelectionWindow->Show(bIsCentralPlotSelectionHidden);
    mDesktop.Add(mCentralPlotSelectionWindow);
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
    mCentralPlotSelectionWindow->Show(!bIsCentralPlotSelectionHidden);
    mDesktop.Update(secondsSinceLastUpdate);
}

void UISCommon::Update(const float secondsSinceLastUpdate)
{
    UpdateCommon(secondsSinceLastUpdate);
}

bool UISCommon::DrawCentralPlotSelectionWindow(Plot::PlotType type,
                                               bool push_front)
{
    bExtendUpwards = push_front;
    bIsCentralPlotSelectionHidden = false;
    return true;
}
