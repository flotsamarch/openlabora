#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <memory>
#include <vector>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Widget.hpp>
#include "GameState/Views/IGameView.hpp"
#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

class GameController;
class AppStateManager;
class Model;

// General UI logic base class
class GameView : public IGameView
{
protected:
    std::weak_ptr<AppStateManager> mState;
    std::shared_ptr<GameController> mController;
    std::shared_ptr<const Model> mModel;
    sfg::Desktop mDesktop;

    sf::Vector2i mMouseCoords;
    sf::Vector2f mMouseDelta{ 0.f, 0.f };

    bool bMouseCapturedByGui{ false };
    bool bEscMenuHidden{ true };
    std::vector<sfg::Widget::Ptr> mMenuWidgets;
    float mEscMenuColWidth;
    sf::Vector2f mScreenCenter;
    float mEscMenuButtonHeight = 40.f;
    float mEscMenuTotalHeight = mEscMenuButtonHeight;

    // These are SFML screenspace<->world coordinate transformation methods
    // They are copied since i cannot pass window around easily
    sf::IntRect TransformViewToWindowCoords(const sf::View&);

    sf::Vector2f MapScreenToWorldCoords(const sf::Vector2i&, const sf::View&);

    sf::Vector2i MapWorldToScreenCoords(const sf::Vector2f&, const sf::View&);

public:
    GameView(std::shared_ptr<AppStateManager>,
             std::shared_ptr<GameController>,
             std::shared_ptr<const Model>);

    virtual ~GameView() noexcept;

    void HandleEvent(const sf::Event& evt) override;

    void Update(const float update_delta_seconds) override;

    void HandleWindowResize(const sf::Vector2u& window_size) override;

    void SetMouseCapturedFlag(bool value) noexcept
    { bMouseCapturedByGui = value; }
};

} // namespace OpenLabora

#endif // GAMEVIEW_HPP_
