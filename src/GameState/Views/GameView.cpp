#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/Button.hpp>
#include "GameState/Views/GameView.hpp"
#include "GameState/Model/Model.hpp"

namespace OpenLabora
{

GameView::GameView(PtrView<IApplication<StateIdsVariant>> app,
                   GameWindow<tgui::GuiSFML, sf::RenderWindow> window,
                   GameController::Ptr controller,
                   Model::PtrConst model)
    : mApp{ app },
      mWindow{ window },
      mController{ controller },
      mModel{ model },
      mMouseCoords{ sf::Mouse::getPosition() }//,
      #if 0 // TODO: Reimplement markers (again)
      mExpansionWindow{ controller },
      mMarkerManager{ controller }
      #endif
{
    const auto win_size = static_cast<sf::Vector2f>(mWindow.GetSize());
    auto position = sf::Vector2f{ -1 * win_size.x / 2, -1 * win_size.y / 2 };
    auto pf_width = static_cast<float>(playfield::kMaxFieldWidth);
    auto pf_height = static_cast<float>(playfield::kMaxFieldHeight);
    position.x += (pf_width / 2) * tile::kTileWidth;
    position.y += (pf_height / 2) * tile::kTileHeight;

    mWindow.SetView(sf::View{ sf::FloatRect{ position, win_size } });

    using Button = tgui::Button;
    #if 0 // TODO: Reimplement markers (again)
    // using MarkerType = ExpansionMarker::MarkerType;
    // using Window = tgui::ChildWindow;
    // using VBox = tgui::VerticalLayout;

    // UI helper lambdas
    auto add_new_plot =
    [&wmarker = mSelectedMarker,
     controller = mController,
     exp_window = mExpansionWindow]
    {
        assert(!wmarker.expired());
        auto marker = wmarker.lock();
        assert(marker != nullptr);

        auto [plot, plot_alt] = marker->GetPlots();

        if (marker->GetPlotType() == Plot::PlotType::Central) {
            const auto toggle_value = exp_window.GetToggleValue();
            assert(toggle_value != 0);
            if (marker->GetType() == MarkerType::Upper) {
                controller->AddPlotToTop(toggle_value < 2 ? plot : plot_alt);
            } else {
                controller->AddPlotToBottom(toggle_value < 2 ? plot : plot_alt);
            }
            return;
        }

        if (marker->GetType() == MarkerType::Upper) {
            controller->AddPlotToTop(plot_alt);
            controller->AddPlotToTop(plot);
        } else {
            controller->AddPlotToBottom(plot);
            controller->AddPlotToBottom(plot_alt);
        }
    };

    auto expansion_win = mExpansionWindow.GetWindow();

    auto close_confirm_window =
    [&window = mExpansionWindow, &wmarker = mSelectedMarker]
    {
        assert(!wmarker.expired());
        auto marker = wmarker.lock();
        if (marker != nullptr) {
            marker->Deselect();
            marker = nullptr;
        }
        window.Show(false);
    };

    auto show_window =
    [&window = mExpansionWindow, &wmarker = this->mSelectedMarker]
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
    #endif
    // Escape menu UI

    auto quit_btn = Button::create("Quit");
    auto resume_btn = Button::create("Resume");

    quit_btn->onPress([app]{ app->ChangeState(FinalStateId{}); });
    resume_btn->onPress([box = mMenuVBox]{ box->setVisible(false); });

    mMenuVBox->setVisible(false);
    mMenuVBox->add(quit_btn, true);
    mMenuVBox->addSpace(0.1f);
    mMenuVBox->add(resume_btn, true);
    mMenuVBox->setOrigin(0.5f, 0.5f);
    mMenuVBox->setPosition("50%", "50%");
    mMenuVBox->setSize("20%", "10%");

    mWindow.AddWidget(mMenuVBox);
    // TODO: Reimplement markers (again)
    #if 0
    mWindow.AddWidget(expansion_win);

    auto confirm_btn = mExpansionWindow.GetConfirmButton();
    auto decline_btn = mExpansionWindow.GetDeclineButton();

    // Order is important
    confirm_btn->onPress(add_new_plot);
    confirm_btn->onPress(close_confirm_window);
    confirm_btn->onPress(update_markers);

    decline_btn->onPress(close_confirm_window);
    expansion_win->onClose(close_confirm_window);

    mMarkerManager.UpdateMarkers(show_window);
    #endif
    // TODO initialize mModel->mBuildGhost something...something...
};

void GameView::HandleEvent(const sf::Event& evt)
{
    switch (evt.type) {
        case sf::Event::KeyPressed:
        {
            if (evt.key.code == sf::Keyboard::Escape) {
                mMenuVBox->setVisible(!mMenuVBox->isVisible());
            }
            break;
        }
        case sf::Event::MouseMoved:
        {
            mMouseDelta.x = static_cast<float>(evt.mouseMove.x - mMouseCoords.x);
            mMouseDelta.y = static_cast<float>(evt.mouseMove.y - mMouseCoords.y);
            mMouseCoords = { evt.mouseMove.x, evt.mouseMove.y };

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
                !mMenuVBox->isVisible())
            {
                auto view = mWindow.GetView();
                view.move({-mMouseDelta.x, -mMouseDelta.y});
                mWindow.SetView(view);
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            // TODO: reimplement in ECS 11.04.2022
            #if 0
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
            #endif

            #if 0 // TODO: Reimplement Build Mode
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
    #if 0 // TODO: Reimplement selectable
    if (!mMenuVBox->isVisible() && !mExpansionWindow.GetWindow()->isVisible())
    {
        auto mouse_world_pos =
            mWindow.MapScreenToWorldCoords(mMouseCoords);

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

    #if 0 // TODO: Reimplement Build Mode.
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

} // namespace OpenLabora
