#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>
#include "AppState/AppStateManager.hpp"
#include "GameState/Views/GameView.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

using PlotType = Plot::PlotType;
using MarkerType = ExpansionMarker::MarkerType;

GameView::GameView(std::shared_ptr<AppStateManager> state,
                   std::shared_ptr<GameController> controller,
                   std::shared_ptr<const Model> model)
    : mState{ state },
      mController{ controller },
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

    // Plot purchase confirmation window
    auto style = static_cast<char>(sfg::Window::Style::BACKGROUND |
                                   sfg::Window::Style::CLOSE |
                                   sfg::Window::Style::RESIZE);
    mPlotConfirmationWindow = sfg::Window::Create(style);

    auto confirm_btn_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    auto confirm_btn_yes = sfg::Button::Create("Yes");
    auto confirm_btn_no = sfg::Button::Create("No");
    confirm_btn_box->Pack(confirm_btn_yes);
    confirm_btn_box->Pack(confirm_btn_no);

    auto confirm_text = sfg::Label::Create("Buy plot?");
    auto confirm_vbox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);
    confirm_vbox->Pack(confirm_btn_box);
    confirm_vbox->Pack(confirm_text);

    mPlotConfirmationWindow->Add(confirm_vbox);
    mPlotConfirmationWindow->Show(false);
    mDesktop.Add(mPlotConfirmationWindow);

    confirm_btn_no->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(
    [window = std::weak_ptr<sfg::Window>(mPlotConfirmationWindow)]
    {
        assert(!window.expired());
        window.lock()->Show(false);
    });

    using PlotType = Plot::PlotType;

    auto&& playfield = mController->GetActivePlayerPlayfield();
    auto&& res_mgr = state->GetResourceManager();

    // Markers
    auto [top_marker_pos, btm_marker_pos] =
        playfield->GetExpansionMarkerPositions(PlotType::Central);

    auto central_plot_top = Plot{Plot::kCentralPlotTop, res_mgr};
    auto central_plot_bottom = Plot{Plot::kCentralPlotBottom, res_mgr};

    auto marker_central_top =
        mController->CreateEntity<ExpansionMarker>(central_plot_top,
                                                   MarkerType::Upper,
                                                   playfield,
                                                   mPlotConfirmationWindow,
                                                   confirm_btn_yes);
    auto marker_central_bottom =
        mController->CreateEntity<ExpansionMarker>(central_plot_bottom,
                                                   MarkerType::Lower,
                                                   playfield,
                                                   mPlotConfirmationWindow,
                                                   confirm_btn_yes);

    RegisterExpansionMarker(marker_central_top);
    RegisterExpansionMarker(marker_central_bottom);
    UpdateMarkers();

    // The deletion of pointers should happen after marker's job is done
    confirm_btn_yes->GetSignal(sfg::Widget::OnMouseLeftRelease).Connect(
    [this]
    {
        this->UpdateMarkers();
    });
    // TODO initialize mModel->mBuildGhost something...something...
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
        case sf::Event::MouseButtonReleased:
        {
            if (bMouseCapturedByGui) {
                break;
            }

            if (evt.mouseButton.button == sf::Mouse::Left) {
                for (auto&& entity : mModel->mSelectableEntities) {
                    if (entity->WasEntered()) {
                        entity->Select();
                    } else {
                        entity->Deselect();
                    }
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

void GameView::UpdateMarkers()
{
    auto playfield = mController->GetActivePlayerPlayfield();

    for (auto&& arr : mMarkers) {
        std::for_each(arr.second.begin(), arr.second.end(),
        [playfield, ctlr = mController] (auto&& marker)
        {
            if (marker != nullptr) {
                auto limit_reached =
                    playfield->IsPlotsLimitReached(marker->GetPlotType(),
                                                   marker->GetType());

                if (limit_reached) {
                    auto mp = std::shared_ptr<ExpansionMarker>(marker);
                    ctlr->RemoveEntity(mp);
                    marker.reset();
                }
            }
        });

        auto&& upper = arr.second[static_cast<size_t>(MarkerType::Upper)];
        auto&& lower = arr.second[static_cast<size_t>(MarkerType::Lower)];

        if (upper != nullptr && lower != nullptr) {
            auto [top_marker_pos, btm_marker_pos] =
                playfield->GetExpansionMarkerPositions(arr.first);
            upper->SetPosition(top_marker_pos);
            lower->SetPosition(btm_marker_pos);
        }
    }
}

void GameView::RegisterExpansionMarker(std::shared_ptr<ExpansionMarker> marker)
{
    auto plot_type = marker->GetPlotType();
    auto marker_type = marker->GetType();
    assert(plot_type != Plot::PlotType::End);
    assert(marker_type != ExpansionMarker::MarkerType::End);
    mMarkers[plot_type][static_cast<std::size_t>(marker_type)] = marker;
}

} // namespace OpenLabora
