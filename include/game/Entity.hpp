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

namespace OpenLabora
{
// Restriction that only allows to Entity class to hold class derived from
// sf::Transformable which all also are sf::Drawable and keep their common
// functionality. No idea why SFML chose not to make a proper interface
template<class T>
concept SFCombined = std::is_base_of<sf::Drawable, T>::value &&
    std::is_base_of<sf::Transformable, T>::value;

template<SFCombined T>
class Entity : public IEntity, public IDrawable, public ITransformable
{
protected:
    T mObject; // Can be sf::Sprite, sf::Shape derivative, sf::Text, etc.
public:
    inline static const sf::Vector2f kOutOfBounds{ -999999.f, -999999.f };
    using Ptr = std::shared_ptr<Entity<T>>;

    virtual ~Entity() noexcept = 0;

    void Move(float offset_x, float offset_y) override
    { mObject.move(offset_x, offset_y); }

    void Move(const sf::Vector2f& offset) override
    { mObject.move(offset); }

    void SetPosition(float position_x, float position_y) override
    { mObject.setPosition(position_x, position_y); }

    void SetPosition(const sf::Vector2f& position) override
    { mObject.setPosition(position); }

    sf::Vector2f GetPosition() const override
    { return mObject.getPosition(); }

    const sf::Drawable& GetDrawableObject() const noexcept override
    { return mObject; }

    bool IsUnderPoint(const sf::Vector2f& point) const override
    { return mObject.getGlobalBounds().contains(point); }
};

template<SFCombined T>
inline Entity<T>::~Entity() noexcept {};

} // namespace OpenLabora

#endif // ENTITY_HPP_
