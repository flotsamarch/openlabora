#ifndef SPRITECOMPONENT_HPP_
#define SPRITECOMPONENT_HPP_

#include <SFML/Graphics/Sprite.hpp>
#include "TextureContainerComponent.hpp"

namespace OpenLabora
{

class SpriteComponent final
{
    sf::Sprite mSprite{};

public:
    void SetTexture(const sf::Texture& texture, bool resetRect = false)
    { mSprite.setTexture(texture, resetRect); }

    void SetPosition(const sf::Vector2f& position)
    { mSprite.setPosition(position); }

    const sf::Vector2f& GetPosition() const
    { return mSprite.getPosition(); }

    void Move(const sf::Vector2f& offset)
    { mSprite.move(offset); }

    decltype(auto) GetLocalBounds() const
    { return mSprite.getLocalBounds(); }

    decltype(auto) GetGlobalBounds() const
    { return mSprite.getGlobalBounds(); }

    const sf::Sprite& GetDrawableObject() const
    { return mSprite; }
};

} // namespace OpenLabora

#endif // SPRITECOMPONENT_HPP_
