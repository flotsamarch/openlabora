// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef SPRITECOMPONENT_HPP_
#define SPRITECOMPONENT_HPP_

#include <SFML/Graphics/Sprite.hpp>
#include "TextureContainerComponent.hpp"

namespace open_labora
{

class SpriteComponent final
{
    sf::Sprite mSprite{};

public:
    void SetTexture(const sf::Texture& texture, bool resetRect = false)
    { mSprite.setTexture(texture, resetRect); }

    void SetPosition(const sf::Vector2f& position)
    { mSprite.setPosition(position); }

    void SetRect(const sf::IntRect& rectangle)
    { mSprite.setTextureRect(rectangle); }

    const sf::Vector2f& GetPosition() const
    { return mSprite.getPosition(); }

    void Move(const sf::Vector2f& offset)
    { mSprite.move(offset); }

    void SetColor(const sf::Color& color)
    { mSprite.setColor(color); }

    decltype(auto) GetLocalBounds() const
    { return mSprite.getLocalBounds(); }

    decltype(auto) GetGlobalBounds() const
    { return mSprite.getGlobalBounds(); }

    const sf::Sprite& GetDrawableObject() const
    { return mSprite; }
};

} // namespace open_labora

#endif // SPRITECOMPONENT_HPP_
