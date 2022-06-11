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
      mMouseCoords{ sf::Mouse::getPosition() },
      mExpansionInterface{ window, controller }
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
};

void GameView::Update([[maybe_unused]]const float update_delta_seconds)
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
    return;
}

} // namespace OpenLabora
