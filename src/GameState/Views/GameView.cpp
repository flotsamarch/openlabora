#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "AppState/AppStateManager.hpp"
#include "GameState/Views/GameView.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

GameView::GameView(std::shared_ptr<AppStateManager> state,
                   std::shared_ptr<IGameController> controller,
                   std::shared_ptr<const Model> model)
    : mState{ state },
      mController{ static_pointer_cast<GameController>(controller) },
      mModel{ model },
      mMouseCoords{ sf::Mouse::getPosition() }
{
    auto&& view = mController->GetMainView();
    auto default_view = sf::FloatRect{ 0.f, 0.f,
            static_cast<float>(mModel->mWindowSize.x),
            static_cast<float>(mModel->mWindowSize.y) };
    view.reset(default_view);

    // Escape menu UI
    auto win_x = static_cast<float>(mModel->mWindowSize.x);
    auto win_y = static_cast<float>(mModel->mWindowSize.y);
    mEscMenuColWidth =  win_x / 3.f;
    mScreenCenter = { win_x / 2.f, win_y / 2.f };

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

    box->SetAllocation(sf::FloatRect(mEscMenuColWidth,
                                     mScreenCenter.y - mEscMenuTotalHeight / 2,
                                     mEscMenuColWidth,
                                     mEscMenuTotalHeight));

    mDesktop.Add(box);
    mMenuWidgets.push_back(box);

    #if 0
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
    #endif // plot selection ui
};

GameView::~GameView() noexcept
{
    mDesktop.RemoveAll();
    mDesktop.Refresh();
};

void GameView::HandleEvent(const sf::Event& evt)
{
    mDesktop.HandleEvent(evt);

    switch (evt.type) {
        case sf::Event::KeyPressed:
        {
            if (evt.key.code == sf::Keyboard::Escape) {
                for (auto& item : mMenuWidgets) {
                    item->Show(bEscMenuHidden);
                    bEscMenuHidden = !bEscMenuHidden;
                }
            }
            break;
        }
        case sf::Event::Resized:
        {
            HandleWindowResize({ evt.size.width, evt.size.height });
            break;
        }
        case sf::Event::MouseMoved:
        {
            mMouseDelta.x = static_cast<float>(evt.mouseMove.x - mMouseCoords.x);
            mMouseDelta.y = static_cast<float>(evt.mouseMove.y - mMouseCoords.y);
            mMouseCoords = { evt.mouseMove.x, evt.mouseMove.y };
            auto mouse_world_pos =
                MapScreenToWorldCoords(mMouseCoords, mModel->mMainView);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && bEscMenuHidden) {
                mController->GetMainView().move(-mMouseDelta.x, -mMouseDelta.y);
            }

            if (bMouseCapturedByGui || !bEscMenuHidden) {
                break;
            }

            // TODO take Z-coordinate into account
            for (auto&& entity : mModel->mSelectableEntities) {
                if (entity->IsPointInRegisteringArea(mouse_world_pos)) {
                    entity->OnHover();
                } else {
                    entity->OnOut();
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (bMouseCapturedByGui) {
                break;
            }

            for (auto&& entity : mModel->mSelectableEntities) {
                if (entity->WasEntered()) {
                    entity->Select(mState.lock());
                }
            }
            // TODO fix build mode
            #if 0
            if (evt.mouseButton.button == sf::Mouse::Left && bBuildModeEnabled) {
                auto pf_position = mPlayfields[Player1]->GetPosition();

                    ChangeLocationTypeAtPoint(mouse_pos_local - pf_position,
                *mPlayfields[Player1],
                mBuildGhost->GetType());

                bBuildModeEnabled = false;
                mBuildGhost->SetPosition(Entity::kOutOfBounds);
            }
            #endif
            break;
        }
        default: { break; }
    }
};

void GameView::Update(const float update_delta_seconds)
{
    mDesktop.Update(update_delta_seconds);

    // Disjunction on all flags that may cause pause in gui
    bool gui_paused = !bEscMenuHidden;
    mController->SetPaused(gui_paused);

    if (mModel->bPaused) {
        return;
    }

    // TODO fix build mode. Move this to GameView
    #if 0
    assert(!mState.expired());
    auto position = sf::Vector2i(mMouseX, mMouseY);
    auto pf_position = mPlayfields[Player1]->GetPosition();
    auto mouse_pos_local = renderer.mapPixelToCoords(position);
    auto tile_info = mPlayfields[Player1]->
        GetTileInfoUnderPoint(mouse_pos_local-pf_position);
    if (tile_info != Tile::kBadTile &&
        bBuildModeEnabled && mBuildGhost != nullptr) {
        mBuildGhost->SetPosition(tile_info.coord);
    } else if (mBuildGhost->GetPosition() != Entity::kOutOfBounds) {
        mBuildGhost->SetPosition(Entity::kOutOfBounds);
    }
    #endif
    return;
}

void GameView::HandleWindowResize(const sf::Vector2u& window_size)
{
    mController->HandleWindowResize(window_size);
    // TODO resizable interface
}

sf::IntRect GameView::TransformViewToWindowCoords(const sf::View& view)
{
    auto width  = static_cast<float>(mModel->mWindowSize.x);
    auto height = static_cast<float>(mModel->mWindowSize.y);
    auto&& viewport = view.getViewport();

    return sf::IntRect({static_cast<int>(0.5f + width  * viewport.left),
                        static_cast<int>(0.5f + height * viewport.top)},
                       {static_cast<int>(0.5f + width  * viewport.width),
                        static_cast<int>(0.5f + height * viewport.height)});
}

sf::Vector2f GameView::MapScreenToWorldCoords(const sf::Vector2i& pixel,
                                              const sf::View& view)
{
    // Convert from viewport coordinates to homogeneous coordinates
    auto viewport = sf::FloatRect(TransformViewToWindowCoords(view));
    auto dx = static_cast<float>(pixel.x) - viewport.left;
    auto dy = static_cast<float>(pixel.y) - viewport.top;

    sf::Vector2f normalized{ -1.f + 2.f * dx / viewport.width,
                              1.f - 2.f * dy / viewport.height };

    // Transform by the inverse of the view matrix
    return view.getInverseTransform().transformPoint(normalized);
}

sf::Vector2i GameView::MapWorldToScreenCoords(const sf::Vector2f& coords,
                                              const sf::View& view)
{
    // Transform the point by the view matrix
    auto normalized = view.getTransform().transformPoint(coords);

    // Convert to viewport coordinates
    auto viewport = sf::FloatRect(TransformViewToWindowCoords(view));
    auto offset_x = (normalized.x + 1.f) / 2.f;
    auto offset_y = (-normalized.y + 1.f) / 2.f;

    return { static_cast<int>(offset_x * viewport.width  + viewport.left),
             static_cast<int>(offset_y * viewport.height + viewport.top)};
}

} // namespace OpenLabora
