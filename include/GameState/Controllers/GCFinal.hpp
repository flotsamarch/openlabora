#ifndef GCFINAL_HPP_
#define GCFINAL_HPP_

#include "GameState/Controllers/IGameController.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

// A controller indicating that app has reached its final state
class GCFinal final : public IGameController
{
public:
    GCFinal(std::shared_ptr<AppStateManager>,
            std::shared_ptr<Model>) {};

    void HandleEvent(const sf::Event&) override {};

    void Update(const float) override {};

    void HandleWindowResize(const sf::Vector2u&) override {};
};

} // namespace OpenLabora

#endif // GCFINAL_HPP_
