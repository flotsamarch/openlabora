#ifndef ITRANSFORMABLE_HPP_
#define ITRANSFORMABLE_HPP_

#include "SFML/System/Vector2.hpp"

class ITransformable
{
public:
    virtual ~ITransformable() noexcept = 0;

    virtual void Move(float offset_x, float offset_y) = 0;

    virtual void Move(const sf::Vector2f& offset) = 0;

    virtual void SetPosition(float offset_x, float offset_y) = 0;

    virtual void SetPosition(const sf::Vector2f& offset) = 0;

    virtual sf::Vector2f GetPosition() const = 0;
};

inline ITransformable::~ITransformable() noexcept {};

#endif // ITRANSFORMABLE_HPP_
