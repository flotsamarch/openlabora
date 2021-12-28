#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "game/IDrawable.hpp"
#include "game/ITransformable.hpp"
#include "resource/IResourceManager.hpp"

class Entity : public IDrawable, public ITransformable
{
protected:
    std::unique_ptr<sf::Transformable> mObject;
public:
    inline static const sf::Vector2f kOutOfBounds{ -999999.f, -999999.f };

    virtual void Move(float offset_x, float offset_y) override
    {
        mObject->move(offset_x, offset_y);
    }

    virtual void Move(const sf::Vector2f& offset) override
    {
        mObject->move(offset);
    }

    virtual void SetPosition(float offset_x, float offset_y) override
    {
        mObject->setPosition(offset_x, offset_y);
    }

    virtual void SetPosition(const sf::Vector2f& offset) override
    {
        mObject->setPosition(offset);
    }

    sf::Vector2f GetPosition() override
    {
        return mObject->getPosition();
    }

    virtual ~Entity() noexcept = 0;
};

inline Entity::~Entity() noexcept {};

#endif // ENTITY_HPP_
