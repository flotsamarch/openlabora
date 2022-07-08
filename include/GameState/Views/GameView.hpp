// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <memory>
#include <TGUI/Widgets/VerticalLayout.hpp>
#include <TGUI/Widgets/Button.hpp>
#include "GameWindow.hpp"
#include "IApplication.hpp"
#include "GameState/Model/Model.hpp"
#include "AppState/StateIds.hpp"
#include "Misc/TupleUtils.hpp"
#include "GUI/Subviews/SubviewInitializer.hpp"

namespace open_labora
{

/**
 * General gameplay-UI logic base class
 *
 * @tparam TGui - GUI library class
 * @tparam TWindow - Render window class
 * @tparam TStateIdsVariant - Variant of all possible IDs for each state.
 * @tparam TGameController - General gameplay logic class
 * @tparam TSubviews - Child views responsible for UI of certain mechanics
 */
template<class TGui, class TWindow, class TStateIdsVariant,
         class TGameController, class... TSubviews>
class GameView
{
    using SubInit = SubviewInitializer<TGui, TWindow, TGameController>;
    static constexpr auto kSubviewCount = sizeof...(TSubviews);

protected:
    using VBox = tgui::VerticalLayout;
    using GameControllerPtr = typename TGameController::Ptr;

    PtrView<IApplication<TStateIdsVariant>> mApp;
    GameWindow<TGui, TWindow> mWindow;
    GameControllerPtr mController;
    Model::PtrConst mModel;

    sf::Vector2i mMouseCoords;
    sf::Vector2f mMouseDelta{ 0.f, 0.f };

    VBox::Ptr mMenuVBox = VBox::create();

private:
    SubInit mSubviewInit{ mWindow, mController };

    auto MakeSubviewInitializer() const
    { return tuple_utils::createTuple<SubInit, kSubviewCount>(mSubviewInit); }

protected:
    std::tuple<TSubviews...> mSubviews{ MakeSubviewInitializer() };

public:
    using Ptr = std::unique_ptr<GameView>;

    GameView(PtrView<IApplication<TStateIdsVariant>>,
             GameWindow<TGui, TWindow>,
             GameControllerPtr,
             Model::PtrConst);

    virtual ~GameView() {};

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);
};

template<class TGui, class TWindow, class TStateIdsVariant,
         class TGameController, class... TSubviews>
GameView<TGui, TWindow, TStateIdsVariant, TGameController, TSubviews...>
::GameView(PtrView<IApplication<TStateIdsVariant>> app,
           GameWindow<TGui, TWindow> window,
           GameControllerPtr controller,
           Model::PtrConst model)
    : mApp{ app },
      mWindow{ window },
      mController{ controller },
      mModel{ model },
      mMouseCoords{ sf::Mouse::getPosition() }
{
    const auto win_size = static_cast<sf::Vector2f>(mWindow.GetSize());
    auto position = sf::Vector2f{ -1 * win_size.x / 2, -1 * win_size.y / 2 };
    auto pf_width = static_cast<float>(playfield::kMaxFieldWidth);
    auto pf_height = static_cast<float>(playfield::kMaxFieldHeight);
    position.x += (pf_width / 2) * tile::kTileWidth;
    position.y += (pf_height / 2) * tile::kTileHeight;

    mWindow.SetView(sf::View{ sf::FloatRect{ position, win_size } });

    using Button = tgui::Button;

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
};

template<class TGui, class TWindow, class TStateIdsVariant,
         class TGameController, class... TSubviews>
void GameView<TGui, TWindow, TStateIdsVariant, TGameController, TSubviews...>
::HandleEvent(const sf::Event& evt)
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

            auto&& world_mouse = mWindow.MapScreenToWorldCoords(mMouseCoords);
            mController->SetWorldMousePosition(world_mouse);

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

    bool handled = false;
    auto handle_evt = [controller = mController, &evt, &handled] (auto&& subview)
    { handled = subviewHandleEvent(subview, controller, evt); };
    auto unhadled_pred = [&handled] (auto&&) { return !handled; };

    tuple_utils::applyUntilFalse(mSubviews, handle_evt, unhadled_pred);
};

template<class TGui, class TWindow, class TStateIdsVariant,
         class TGameController, class... TSubviews>
void GameView<TGui, TWindow, TStateIdsVariant, TGameController, TSubviews...>
::Update(const float update_delta_seconds)
{
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
    auto update = [ctlr = mController, update_delta_seconds] (auto&& subview)
    { subviewUpdate(subview, ctlr, update_delta_seconds); };
    std::apply(update, mSubviews);
}

} // namespace open_labora

#endif // GAMEVIEW_HPP_
