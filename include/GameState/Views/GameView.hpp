#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <memory>
#include <vector>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
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
    PtrView<IApplication<StateIdsVariant>> mApp;
    GameController::Ptr mController;
    PtrView<tgui::GuiSFML> mGui;
    PtrView<const Model> mModel;

    sf::Vector2i mMouseCoords;
    sf::Vector2f mMouseDelta{ 0.f, 0.f };

    bool bEscMenuHidden{ true };
    // TODO Fix UI: Escape menu
    // std::vector<sfg::Widget::Ptr> mMenuWidgets;
    float mEscMenuColWidth;
    sf::Vector2f mScreenCenter;
    float mEscMenuButtonHeight = 40.f;
    float mEscMenuTotalHeight = mEscMenuButtonHeight;

    std::shared_ptr<Location> mBuildGhost;

    // TODO Fix UI: Bring markers back
    // MarkerManager mMarkerManager;
    // ExpansionWindow mExpansionWindow;

    std::weak_ptr<ExpansionMarker> mSelectedMarker; // Owned by Model

    // These are SFML screenspace<->world coordinate transformation methods
    // They are copied since i cannot pass window around easily
    sf::IntRect TransformViewToWindowCoords(const sf::View&);

    sf::Vector2f MapScreenToWorldCoords(const sf::Vector2i&, const sf::View&);

    sf::Vector2i MapWorldToScreenCoords(const sf::Vector2f&, const sf::View&);

public:
    GameView(PtrView<IApplication<StateIdsVariant>>,
             PtrView<tgui::GuiSFML>,
             GameController::Ptr,
             PtrView<const Model>);

    virtual ~GameView() noexcept {};

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);

    void HandleWindowResize(const sf::Vector2u& window_size);
};

} // namespace OpenLabora

#endif // GAMEVIEW_HPP_
