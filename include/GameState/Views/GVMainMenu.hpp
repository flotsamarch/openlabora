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

#ifndef GVMAINMENU_HPP_
#define GVMAINMENU_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "IApplication.hpp"
#include "GameWindow.hpp"
#include "Misc/PtrView.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Model/NoModel.hpp"

namespace open_labora
{

class GCMainMenu;

// General UI logic base class
class GVMainMenu final
{
    PtrView<IApplication<StateIdsVariant>> mApp;
    GameWindow<tgui::GuiSFML, sf::RenderWindow> mWindow;
    std::shared_ptr<GCMainMenu> mController;
    NoModel::PtrConst mModel;

public:
    using Ptr = std::unique_ptr<GVMainMenu>;

    GVMainMenu(PtrView<IApplication<StateIdsVariant>>,
               GameWindow<tgui::GuiSFML, sf::RenderWindow>,
               std::shared_ptr<GCMainMenu>,
               NoModel::PtrConst);

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);
};

} // namespace open_labora

#endif // GVMAINMENU_HPP_
