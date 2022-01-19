#ifndef GVMAINMENU_HPP_
#define GVMAINMENU_HPP_

#include <memory>
#include <vector>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Widget.hpp>
#include "GameState/Views/IGameView.hpp"
#include "GameState/Controllers/IGameController.hpp"

namespace OpenLabora
{

class GameController;
class AppStateManager;
class Model;

// General UI logic base class
class GVMainMenu final : public IGameView
{
protected:
    std::weak_ptr<AppStateManager> mState;
    std::shared_ptr<IGameController> mController;
    std::shared_ptr<const Model> mModel;
    sfg::Desktop mDesktop;

public:
    GVMainMenu(std::shared_ptr<AppStateManager>,
             std::shared_ptr<IGameController>,
             std::shared_ptr<const Model>);

    ~GVMainMenu() noexcept;

    void HandleEvent(const sf::Event& evt) override;

    void Update(const float update_delta_seconds) override;

    void HandleWindowResize(const sf::Vector2u& window_size) override;
};

} // namespace OpenLabora

#endif // GVMAINMENU_HPP_
