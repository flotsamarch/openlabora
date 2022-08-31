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

#include "LibTypedefs.hpp"

namespace open_labora
{

class SpriteComponent final
{
    Sprite mSprite{};

public:
    void SetTexture(const Texture& texture, bool resetRect = false)
    { mSprite.setTexture(texture, resetRect); }

    void SetPosition(const Vector2f& position)
    { mSprite.setPosition(position); }

    void SetRect(const IntRect& rectangle)
    { mSprite.setTextureRect(rectangle); }

    const Vector2f& GetPosition() const
    { return mSprite.getPosition(); }

    void Move(const Vector2f& offset)
    { mSprite.move(offset); }

    void SetColor(const Color& color)
    { mSprite.setColor(color); }

    FloatRect GetLocalBounds() const
    { return mSprite.getLocalBounds(); }

    FloatRect GetGlobalBounds() const
    { return mSprite.getGlobalBounds(); }

    const Drawable& GetDrawableObject() const
    { return mSprite; }
};

} // namespace open_labora

#endif // SPRITECOMPONENT_HPP_
