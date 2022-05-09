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
