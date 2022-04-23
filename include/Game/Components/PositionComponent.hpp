#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include <SFML/System/Vector2.hpp>

namespace OpenLabora
{

struct PositionComponent final
{
    sf::Vector2f position;

    PositionComponent() : position{} {};

    PositionComponent(sf::Vector2f position_) : position{ position_ } {};
};

} // namespace OpenLabora

#endif // POSITIONCOMPONENT_HPP_
