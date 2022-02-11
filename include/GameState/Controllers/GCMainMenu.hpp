#ifndef GCMAINMENU_HPP_
#define GCMAINMENU_HPP_

#include <memory>
#include "IGameController.hpp"

namespace OpenLabora
{

class Model;
class AppStateManager;

class GCMainMenu final : public IGameController
{
public:
    std::weak_ptr<AppStateManager> mState;
    std::shared_ptr<Model> mModel;
    GCMainMenu(std::shared_ptr<AppStateManager>, std::shared_ptr<Model>);
    ~GCMainMenu();

    void HandleEvent(const sf::Event&) override;

    void Update(const float update_delta_seconds) override;

    void HandleWindowResize(const sf::Vector2u&) override {};
};

} // namespace OpenLabora

#endif // GCMAINMENU_HPP_
