#ifndef ILOGICSTATE_HPP_
#define ILOGICSTATE_HPP_

#include <SFML/Window/Event.hpp>

class ILogicState
{
public:
    virtual ~ILogicState() noexcept {};

    virtual void HandleEvent(const sf::Event&) = 0;

    virtual void HandleEventImpl(const sf::Event&) = 0;

    virtual void Update(const float secondsSinceLastUpdate) = 0;
};

#endif // ILOGICSTATE_HPP_
