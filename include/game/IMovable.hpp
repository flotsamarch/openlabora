#ifndef IMOVABLE_HPP_
#define IMOVABLE_HPP_

#include "SFML/System/Vector2.hpp"

class IMovable
{
public:
    virtual ~IMovable() noexcept = 0;

    virtual void Move(float offset_x, float offset_y) = 0;

    virtual void Move(const sf::Vector2f& offset) = 0;

    virtual void SetPosition(float offset_x, float offset_y) = 0;

    virtual void SetPosition(const sf::Vector2f& offset) = 0;

    virtual sf::Vector2f GetPosition() = 0;
};

inline IMovable::~IMovable() noexcept {};

#endif // IMOVABLE_HPP_
