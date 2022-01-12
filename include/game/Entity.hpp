#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <memory>
#include <concepts>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "IEntity.hpp"
#include "IDrawable.hpp"
#include "ITransformable.hpp"
#include "resource/IResourceManager.hpp"

class Entity : public IEntity, public IDrawable, public ITransformable
{
protected:
    sf::Sprite mObject;
public:
    inline static const sf::Vector2f kOutOfBounds{ -999999.f, -999999.f };
    virtual ~Entity() noexcept = 0;

    void Move(float offset_x, float offset_y) override
    {
        mObject.move(offset_x, offset_y);
    }

    void Move(const sf::Vector2f& offset) override
    {
        mObject.move(offset);
    }

    void SetPosition(float offset_x, float offset_y) override
    {
        mObject.setPosition(offset_x, offset_y);
    }

    void SetPosition(const sf::Vector2f& offset) override
    {
        mObject.setPosition(offset);
    }

    sf::Vector2f GetPosition() const override
    {
        return mObject.getPosition();
    }

    const sf::Drawable& GetDrawableObject() const noexcept override
    {
        return mObject;
    }

    bool IsUnderPoint(const sf::Vector2f& point) const override
    {
        return mObject.getGlobalBounds().contains(point);
    }
};

inline Entity::~Entity() noexcept {};

#endif // ENTITY_HPP_
