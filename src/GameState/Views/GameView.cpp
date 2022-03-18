#include <ranges>
#include "GameState/Views/GameView.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

GameView::GameView(PtrView<IApplication<StateIdsVariant>> app,
                   GameWindow<tgui::GuiSFML, sf::RenderWindow> window,
                   GameController::Ptr controller,
                   Model::CPtr model)
    : mApp{ app },
      mWindow{ window },
      mController{ controller },
      mModel{ model },
      mMouseCoords{ sf::Mouse::getPosition() }
      // TODO Fix UI: Bring markers back
      // mExpansionWindow{ controller },
      // mMarkerManager{ controller, state->GetResourceManager() }
{
    auto win_size = static_cast<sf::Vector2f>(mWindow.GetSize());
    auto position = sf::Vector2f{ -1 * win_size.x / 2, -1 * win_size.y / 2 };
    auto pf_width = static_cast<float>(Playfield::kMaxFieldWidth);
    auto pf_height = static_cast<float>(Playfield::kMaxFieldHeight);
    position.x += (pf_width / 2) * Tile::kTileWidth;
    position.y += (pf_height / 2) * Tile::kTileHeight;

    mWindow.SetView(sf::View {
            sf::FloatRect{position, win_size}
        });
    // TODO Fix UI
    #if 0
    using MarkerType = ExpansionMarker::MarkerType;


    // UI helper lambdas

    // Generate delegate for SFGUI that closes specific window
    auto close_window =
    [] (Window::Ptr window)
    {
        return [window = std::weak_ptr<Window>(window)]
        {
                assert(!window.expired());
                window.lock()->Show(false);
        };
    };

    auto center_window =
    [&screen_size = mModel->GetWindowSize()]
    (Window::Ptr window, sf::Vector2f window_size)
    {
        auto half_width = window_size.x / 2;
        auto half_height = window_size.y / 2;
        auto center_x = screen_size.x / 2;
        auto center_y = screen_size.y / 2;

        window->SetAllocation({center_x - half_width,
                               center_y - half_height,
                               window_size.x,
                               window_size.y});
    };

    auto add_new_plot =
    [&wmarker = mSelectedMarker, wctlr = GameController::WPtr{ mController }]
    {
        assert(!wmarker.expired());
        assert(!wctlr.expired());
        auto marker = wmarker.lock();
        auto ctlr = wctlr.lock();
        assert(marker != nullptr);

        auto [plot_top, plot_bottom] = marker->GetPlots();
        const bool is_multiplot = plot_bottom != std::nullopt;

        if (marker->GetType() == MarkerType::Upper) {
            if (is_multiplot)
            {
                ctlr->AddPlotToTop(plot_bottom.value());
            }
            ctlr->AddPlotToTop(plot_top);
        } else {
            ctlr->AddPlotToBottom(plot_top);
            if (is_multiplot)
            {
                ctlr->AddPlotToBottom(plot_bottom.value());
            }
        }
    };

    auto expansion_win = mExpansionWindow.GetWindow();

    auto close_confirm_window =
    [close = close_window(expansion_win),
     &wmarker = mSelectedMarker]
    {
        assert(!wmarker.expired());
        auto marker = wmarker.lock();
        if (marker != nullptr) {
            marker->Deselect();
            marker = nullptr;
        }
        close();
    };

    auto show_window =
    [&window = mExpansionWindow, &wmarker = mSelectedMarker]
    {
        assert(!wmarker.expired());
        auto marker = wmarker.lock();
        assert(marker != nullptr);
        window.SetState(marker->GetPlotType());
        window.Show(true);
    };

    auto update_markers =
    [&manager = mMarkerManager, show_window]
    { manager.UpdateMarkers(show_window); };

    // Escape menu UI
    mEscMenuColWidth =  win_size.x / 3.f;
    mScreenCenter = { win_size.x / 2.f, win_size.y / 2.f };

    auto quit_btn = sfg::Button::Create("Quit");

    connect(quit_btn, Widget::OnLeftClick,
    [state = mState]
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

    center_window(expansion_win, {350.f, 90.f});
    mDesktop.Add(expansion_win);

    auto confirm_btn = mExpansionWindow.GetConfirmButton();
    auto decline_btn = mExpansionWindow.GetDeclineButton();

    // Order is important
    connect(confirm_btn, Widget::OnMouseLeftRelease, add_new_plot);
    connect(confirm_btn, Widget::OnMouseLeftRelease, close_confirm_window);
    connect(confirm_btn, Widget::OnMouseLeftRelease, update_markers);

    connect(decline_btn, Widget::OnMouseLeftRelease, close_confirm_window);

    connect(expansion_win, Window::OnCloseButton, close_confirm_window);

    mMarkerManager.UpdateMarkers(show_window);
    #endif
    // TODO initialize mModel->mBuildGhost something...something...
};

void GameView::HandleEvent(const sf::Event& evt)
{
    switch (evt.type) {
        case sf::Event::KeyPressed:
        {
            // TODO Fix UI: Escape-menu
            #if 0
            if (evt.key.code == sf::Keyboard::Escape) {
                for (auto& item : mMenuWidgets) {
                    item->Show(bEscMenuHidden);
                    bEscMenuHidden = !bEscMenuHidden;
                }
            }
            #endif
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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && bEscMenuHidden) {
                auto view = mWindow.GetView();
                view.move({-mMouseDelta.x, -mMouseDelta.y});
                mWindow.SetView(view);
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (evt.mouseButton.button == sf::Mouse::Left) {
                auto begin = mModel->GetSelectableEntities().begin();
                auto end = mModel->GetSelectableEntities().end();
                for (auto it_entity = begin; it_entity != end; ++it_entity) {
                    auto entity = *it_entity;
                    if (entity->WasEntered()) {
                        // This is not too bad but perhaps there is a better way
                        using Marker = ExpansionMarker;
                        auto marker = std::dynamic_pointer_cast<Marker>(entity);
                        if (marker != nullptr) {
                            mSelectedMarker = marker;
                        }
                        entity->Select();
                    } else {
                        entity->Deselect();
                        auto selected_marker = mSelectedMarker.lock();
                        if (entity == selected_marker) {
                            selected_marker = nullptr;
                        }
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
        default: {}
    }
};

void GameView::Update([[maybe_unused]]const float update_delta_seconds)
{
    // TODO fix iteration over Selectable entities
    #if 0
    if (bEscMenuHidden && !mExpansionWindow.GetWindow()->IsGloballyVisible())
    {
        auto mouse_world_pos =
            MapScreenToWorldCoords(mMouseCoords, mModel->GetMainView());

        // TODO Take Z-coordinate into account
        auto begin = mModel->GetSelectableEntities().begin();
        auto end = mModel->GetSelectableEntities().end();
        for (auto it_entity = begin; it_entity != end; ++it_entity) {
            auto entity = *it_entity;
            if (entity->IsPointInRegisteringArea(mouse_world_pos)) {
                entity->OnHover();
            } else {
                entity->OnOut();
            }
        }
    }
    #endif

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

} // namespace OpenLabora
