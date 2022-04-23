#ifndef TEXTURECONTAINERCOMPONENT_HPP_
#define TEXTURECONTAINERCOMPONENT_HPP_

#include <SFML/Graphics/Texture.hpp>

namespace OpenLabora
{

class TextureContainerComponent final
{
    sf::Texture mTexture{};
    bool bNeedsUpdate{ true };

public:
    bool NeedsUpdate() const noexcept
    { return bNeedsUpdate; }

    void MarkUpdated(bool value) noexcept
    { bNeedsUpdate = !value; }

    void SetTexture(const sf::Texture& other)
    { mTexture = other; }

    const sf::Texture& GetTexture() const noexcept
    { return mTexture; };
};

} // namespace OpenLabora

#endif // TEXTURECONTAINERCOMPONENT_HPP_
