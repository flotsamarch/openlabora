#ifndef GVFINAL_HPP_
#define GVFINAL_HPP_

#include <memory>
#include "GameState/Controllers/IGameController.hpp"
#include "GameState/Views/IGameView.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

class AppStateManager;

// A view indicating that app has reached its final state
class GVFinal final : public IGameView
{
public:
    GVFinal(std::shared_ptr<AppStateManager>,
            std::shared_ptr<IGameController>,
            std::shared_ptr<const Model>) {};

    void HandleEvent(const sf::Event&) override {};

    void Update(const float) override {};

    void HandleWindowResize(const sf::Vector2u&) override {};
};

} // namespace OpenLabora

#endif // GVFINAL_HPP_
