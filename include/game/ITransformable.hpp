#ifndef ITRANSFORMABLE_HPP_
#define ITRANSFORMABLE_HPP_

#include "SFML/System/Vector2.hpp"

namespace OpenLabora
{

class ITransformable
{
public:
    virtual ~ITransformable() {};

    virtual void Move(float offset_x, float offset_y) = 0;

    virtual void Move(const sf::Vector2f& offset) = 0;

    virtual void SetPosition(float position_x, float position_y) = 0;

    virtual void SetPosition(const sf::Vector2f& position) = 0;

    virtual sf::Vector2f GetPosition() const = 0;
};

} // namespace OpenLabora

#endif // ITRANSFORMABLE_HPP_
