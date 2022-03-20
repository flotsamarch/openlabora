#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <memory>
#include <vector>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>
#include "GameWindow.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "IApplication.hpp"
#include "AppState/StateIds.hpp"
#include "Game/MarkerManager.hpp"
#include "GUI/ExpansionWindow.hpp"

namespace OpenLabora
{

class Model;

// General gameplay UI logic base class
class GameView
{
protected:
    using VBox = tgui::VerticalLayout;

    PtrView<IApplication<StateIdsVariant>> mApp;
    GameWindow<tgui::GuiSFML, sf::RenderWindow> mWindow;
    GameController::Ptr mController;
    Model::CPtr mModel;

    sf::Vector2i mMouseCoords;
    sf::Vector2f mMouseDelta{ 0.f, 0.f };

    std::shared_ptr<Location> mBuildGhost;

    VBox::Ptr mMenuVBox = VBox::create();
    MarkerManager mMarkerManager;
    ExpansionWindow mExpansionWindow;

    std::weak_ptr<ExpansionMarker> mSelectedMarker; // Owned by Model

public:
    using Ptr = std::unique_ptr<GameView>;

    GameView(PtrView<IApplication<StateIdsVariant>>,
             GameWindow<tgui::GuiSFML, sf::RenderWindow>,
             GameController::Ptr,
             Model::CPtr);

    virtual ~GameView() noexcept {};

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);

    void HandleWindowResize(const sf::Vector2u& window_size);
};

} // namespace OpenLabora

#endif // GAMEVIEW_HPP_
