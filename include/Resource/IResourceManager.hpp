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

#ifndef IRESOURCEMANAGER_HPP_
#define IRESOURCEMANAGER_HPP_

#include <memory>
#include <string_view>
#include <optional>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace open_labora
{

class IResourceManager
{
    using TextureRef = std::reference_wrapper<const sf::Texture>;
public:
    using Ptr = std::shared_ptr<IResourceManager>;
    using OptionalTextureRef = std::optional<TextureRef>;

    virtual const sf::Texture&
    GetTextureOrDefault(std::string_view name) const = 0;

    virtual OptionalTextureRef GetTexture(std::string_view name) const = 0;

    virtual const sf::Texture&
    RegisterTexture(std::string_view name, const sf::Texture&) = 0;

    virtual ~IResourceManager() = default;
};

} // namespace open_labora

#endif // IRESOURCEMANAGER_HPP_
