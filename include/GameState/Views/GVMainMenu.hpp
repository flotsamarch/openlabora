#ifndef GVMAINMENU_HPP_
#define GVMAINMENU_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "AppState/StateIds.hpp"

namespace OpenLabora
{

class Model;
class GCMainMenu;

// General UI logic base class
class GVMainMenu final
{
    PtrView<IApplication<StateIdsVariant>> mApp;
    PtrView<tgui::GuiSFML> mGui;
    std::shared_ptr<GCMainMenu> mController;
    PtrView<const Model> mModel;

public:
    GVMainMenu(PtrView<IApplication<StateIdsVariant>>,
               PtrView<tgui::GuiSFML>,
               std::shared_ptr<GCMainMenu>,
               PtrView<const Model>);

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);

    void HandleWindowResize(const sf::Vector2u& window_size);
};

} // namespace OpenLabora

#endif // GVMAINMENU_HPP_
