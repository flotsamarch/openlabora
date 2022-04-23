#ifndef IMMOBILECOMPONENT_HPP_
#define IMMOBILECOMPONENT_HPP_

#include <SFML/System/Vector2.hpp>

namespace OpenLabora
{

class ImmobileComponent final
{
    sf::Vector2f mPosition;

public:
    ImmobileComponent(const sf::Vector2f& initial_pos)
        : mPosition{ initial_pos } {};

    auto GetPosition() const { return mPosition; }
};

} // namespace OpenLabora

#endif // IMMOBILECOMPONENT_HPP_
