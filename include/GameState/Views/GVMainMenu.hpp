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
#include "GameState/Model.hpp"

namespace OpenLabora
{

class GCMainMenu;

// General UI logic base class
class GVMainMenu final
{
    PtrView<IApplication<StateIdsVariant>> mApp;
    GameWindow<tgui::GuiSFML, sf::RenderWindow> mWindow;
    std::shared_ptr<GCMainMenu> mController;
    NoModel::CPtr mModel;

public:
    using Ptr = std::unique_ptr<GVMainMenu>;

    GVMainMenu(PtrView<IApplication<StateIdsVariant>>,
               GameWindow<tgui::GuiSFML, sf::RenderWindow>,
               std::shared_ptr<GCMainMenu>,
               NoModel::CPtr);

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);
};

} // namespace OpenLabora

#endif // GVMAINMENU_HPP_
