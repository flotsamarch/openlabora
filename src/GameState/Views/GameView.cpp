#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include <SFGUI/Label.hpp>
#include <SFGUI/Alignment.hpp>
#include "AppState/AppStateManager.hpp"
#include "GameState/Views/GameView.hpp"
#include "GameState/Model.hpp"
#include "GUI/Utility.hpp"

namespace OpenLabora
{

namespace
{
using PlotType = Plot::PlotType;
using MarkerType = ExpansionMarker::MarkerType;
}

GameView::GameView(std::shared_ptr<AppStateManager> state,
                   std::shared_ptr<GameController> controller,
                   std::shared_ptr<const Model> model)
    : mState{ state },
      mController{ controller },
      mModel{ model },
      mMouseCoords{ sf::Mouse::getPosition() }
{
    using Widget = sfg::Widget;
    using Window = sfg::Window;

    auto win_size = static_cast<sf::Vector2f>(mModel->GetWindowSize());
    mController->ResetMainView(sf::FloatRect{0.f, 0.f, win_size.x, win_size.y});

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

    // Plot purchase confirmation window
    auto style = static_cast<char>(Window::Style::BACKGROUND |
                                   Window::Style::TITLEBAR |
                                   Window::Style::SHADOW |
                                   Window::Style::CLOSE);
    mPlotConfirmWindow = CreateEventConsumingWidget<Window>(style);

    auto confirm_btn_yes = CreateEventConsumingWidget<sfg::Button>("Yes");
    auto confirm_btn_no = CreateEventConsumingWidget<sfg::Button>("No");
    auto confirm_btn_box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);
    confirm_btn_box->Pack(confirm_btn_yes);
    confirm_btn_box->Pack(confirm_btn_no);

    auto confirm_text = sfg::Label::Create("Buy plot?");
    auto confirm_vbox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 10.f);
    confirm_vbox->Pack(confirm_text);
    confirm_vbox->Pack(confirm_btn_box);

    mPlotConfirmWindow->Add(confirm_vbox);
    mPlotConfirmWindow->Show(false);

    auto close_confirm_window = close_window(mPlotConfirmWindow);
    connect(mPlotConfirmWindow, Window::OnCloseButton, close_confirm_window);
    connect(confirm_btn_no, Widget::OnMouseLeftRelease, close_confirm_window);
    connect(confirm_btn_yes, Widget::OnMouseLeftRelease, close_confirm_window);

    center_window(mPlotConfirmWindow, {350.f, 90.f});
    mDesktop.Add(mPlotConfirmWindow);

    #if 0
    using PlotType = Plot::PlotType;
    auto&& res_mgr = state->GetResourceManager();

    // Markers
    auto coastal_plot = Plot{Plot::kCostalPlot, res_mgr};

    auto marker_coastal_top = mController->CreateMarker(coastal_plot,
                                                        MarkerType::Upper,
                                                        mPlotConfirmWindow,
                                                        confirm_btn_yes);
    auto marker_coastal_middle = mController->CreateMarker(coastal_plot,
                                                           MarkerType::Disposable,
                                                           mPlotConfirmWindow,
                                                           confirm_btn_yes);
    auto marker_coastal_bottom = mController->CreateMarker(coastal_plot,
                                                           MarkerType::Lower,
                                                           mPlotConfirmWindow,
                                                           confirm_btn_yes);

    auto central_plot_top = Plot{Plot::kCentralPlotTop, res_mgr};
    auto central_plot_bottom = Plot{Plot::kCentralPlotBottom, res_mgr};

    auto marker_central_top = mController->CreateMarker(central_plot_top,
                                                        MarkerType::Upper,
                                                        mPlotConfirmWindow,
                                                        confirm_btn_yes);
    auto marker_central_bottom = mController->CreateMarker(central_plot_bottom,
                                                           MarkerType::Lower,
                                                           mPlotConfirmWindow,
                                                           confirm_btn_yes);

    auto mountain_plot_top = Plot{Plot::kMountainPlotTop, res_mgr};
    auto mountain_plot_bottom = Plot{Plot::kMountainPlotBottom, res_mgr};

    auto marker_mountain_top = mController->CreateMarker(mountain_plot_top,
                                                         MarkerType::Upper,
                                                         mPlotConfirmWindow,
                                                         confirm_btn_yes);
    auto marker_mountain_middle = mController->CreateMarker(mountain_plot_top,
                                                            MarkerType::Disposable,
                                                            mPlotConfirmWindow,
                                                            confirm_btn_yes);
    auto marker_mountain_bottom = mController->CreateMarker(mountain_plot_top,
                                                            MarkerType::Lower,
                                                            mPlotConfirmWindow,
                                                            confirm_btn_yes);

    auto position = mController->GetActivePlayerPlayfield()->GetPosition();
    position.y += Playfield::kInitialPlotOffset;
    marker_coastal_middle->SetPosition(position);
    position.x += Plot::GetOffsetXForPlotType(PlotType::Mountain);
    marker_mountain_middle->SetPosition(position);

    RegisterExpansionMarker(marker_coastal_top);
    RegisterExpansionMarker(marker_coastal_middle);
    RegisterExpansionMarker(marker_coastal_bottom);
    RegisterExpansionMarker(marker_central_top);
    RegisterExpansionMarker(marker_central_bottom);
    RegisterExpansionMarker(marker_mountain_top);
    RegisterExpansionMarker(marker_mountain_middle);
    RegisterExpansionMarker(marker_mountain_bottom);

    UpdateMarkers();
    // The deletion of pointers should happen after marker's job is done
    connect(confirm_btn_yes, Widget::OnMouseLeftRelease,
    [this]
    {
        this->UpdateMarkers();
    });
    #endif
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

    mPlotConfirmWindow->IsLocallyVisible();

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

            if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && bEscMenuHidden) {
                mController->MoveMainView({-mMouseDelta.x, -mMouseDelta.y});
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (mModel->IsEventIgnored(evt.type)) {
                break;
            }

            if (evt.mouseButton.button == sf::Mouse::Left) {
                auto begin = mModel->GetSelectableEntities().begin();
                auto end = mModel->GetSelectableEntities().end();
                for (auto entity = begin; entity != end; ++entity) {
                    if ((*entity)->WasEntered()) {
                        mController->SelectEntity(entity);
                    } else {
                        mController->DeselectEntity(entity);
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

void GameView::Update(const float update_delta_seconds)
{
    mDesktop.Update(update_delta_seconds);

    if (bEscMenuHidden && !mPlotConfirmWindow->IsGloballyVisible())
    {
        auto mouse_world_pos =
            MapScreenToWorldCoords(mMouseCoords, mModel->GetMainView());

        // Todo Take Z-coordinate into account
        auto begin = mModel->GetSelectableEntities().begin();
        auto end = mModel->GetSelectableEntities().end();
        for (auto entity = begin; entity != end; ++entity) {
            if ((*entity)->IsPointInRegisteringArea(mouse_world_pos)) {
                mController->EntityOnHover(entity);
            } else {
                mController->EntityOnOut(entity);
            }
        }
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
    auto win_size  = static_cast<sf::Vector2f>(mModel->GetWindowSize());
    auto&& viewport = view.getViewport();

    return sf::IntRect({static_cast<int>(0.5f + win_size.x * viewport.left),
                        static_cast<int>(0.5f + win_size.y * viewport.top)},
                       {static_cast<int>(0.5f + win_size.x * viewport.width),
                        static_cast<int>(0.5f + win_size.y * viewport.height)});
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
                auto plot_type = marker->GetPlotType();
                auto marker_type = marker->GetType();
                if (playfield->IsPlotsLimitReached(plot_type, marker_type))
                {
                    ctlr->RemoveMarker(marker);
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
