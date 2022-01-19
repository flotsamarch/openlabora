#ifndef IGAMEVIEW_HPP_
#define IGAMEVIEW_HPP_

#include <SFML/Window/Event.hpp>

namespace OpenLabora
{

class IGameView
{
public:
    virtual ~IGameView() {};

    virtual void HandleEvent(const sf::Event&) = 0;

    virtual void Update(const float update_delta_seconds) = 0;

    virtual void HandleWindowResize(const sf::Vector2u& window_size) = 0;
};

} // namespace OpenLabora

#endif // IGAMEVIEW_HPP_
