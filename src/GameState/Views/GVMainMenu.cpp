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

#include <TGUI/Widgets/VerticalLayout.hpp>
#include <TGUI/Widgets/Button.hpp>
#include "GameState/Views/GVMainMenu.hpp"
#include "AppState/StateIds.hpp"

namespace OpenLabora
{

GVMainMenu::GVMainMenu(PtrView<IApplication<StateIdsVariant>> app,
                       GameWindow<tgui::GuiSFML, sf::RenderWindow> window,
                       std::shared_ptr<GCMainMenu> controller,
                       NoModel::PtrConst model)
    : mApp{ app }, mWindow{ window }, mController{ controller }, mModel{ model }
{
    auto win_size = static_cast<sf::Vector2f>(mWindow.GetSize());
    auto box_padding_ratio = 0.1f;

    auto vbox = tgui::VerticalLayout::create();
    vbox->setOrigin(0.5f, 0.5f);
    vbox->setPosition("50%", "50%");
    vbox->setSize("20%", "10%");

    auto duel_btn = tgui::Button::create("Duel");
    auto quit_btn = tgui::Button::create("Quit");

    duel_btn->onPress([app]{ app->ChangeState(DuelStateId{}); });
    quit_btn->onPress([app]{ app->ChangeState(FinalStateId{}); });

    vbox->add(duel_btn);
    vbox->addSpace(box_padding_ratio);
    vbox->add(quit_btn);

    mWindow.AddWidget(vbox);
};

void GVMainMenu::HandleEvent([[maybe_unused]]const sf::Event& evt)
{
};

void GVMainMenu::Update([[maybe_unused]]const float update_delta_seconds)
{
}

} // namespace OpenLabora
