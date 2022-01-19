#ifndef IGAMECONTROLLER_HPP_
#define IGAMECONTROLLER_HPP_

#include <SFML/Window/Event.hpp>
#include "Game/Location.hpp"

namespace OpenLabora
{

class IGameController
{
public:
    virtual ~IGameController() {};

    virtual void HandleEvent(const sf::Event&) = 0;

    virtual void Update(const float update_delta_seconds) = 0;
};

} // namespace OpenLabora

#endif // IGAMECONTROLLER_HPP_
