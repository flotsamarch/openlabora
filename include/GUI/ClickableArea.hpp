#ifndef CLICKABLEAREA_HPP_
#define CLICKABLEAREA_HPP_

#include <SFML/Graphics/Shape.hpp>
#include "game/ITransformable.hpp"

namespace OpenLabora
{

template<class TShape>
requires std::is_base_of<sf::Shape, TShape>::value
class ClickableArea final : public ITransformable
{
    TShape mShape;
    sf::Vector2f mShapeOffset;

public:
    ClickableArea() = default;

    template<class... Args>
    ClickableArea(const sf::Vector2f& offset, Args... args)
        : mShape{ std::forward<Args>(args)... }, mShapeOffset{ offset } {}

    sf::FloatRect GetLocalBounds() const
    { return mShape.getLocalBounds(); }

    sf::FloatRect GetGlobalBounds() const
    { return mShape.getGlobalBounds(); }

    void Move(float offset_x, float offset_y) override
    { mShape.move(offset_x, offset_y); }

    void Move(const sf::Vector2f& offset) override
    { mShape.move(offset); }

    void SetPosition(float position_x, float position_y) override
    {
        mShape.setPosition(position_x + mShapeOffset.x,
                           position_y + mShapeOffset.y);
    }

    void SetPosition(const sf::Vector2f& position) override
    { mShape.setPosition(position + mShapeOffset); }

    sf::Vector2f GetPosition() const override
    { return mShape.getPosition(); }

};

}// namespace OpenLabora

#endif // CLICKABLEAREA_HPP_
