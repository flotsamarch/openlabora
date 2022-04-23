#ifndef IRESOURCEMANAGER_HPP_
#define IRESOURCEMANAGER_HPP_

#include <memory>
#include <string_view>
#include <optional>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace OpenLabora
{

class IResourceManager
{
public:
    using Ptr = std::shared_ptr<IResourceManager>;

    virtual const sf::Texture&
    GetTextureOrDefault(std::string_view name) const = 0;

    virtual std::optional<std::reference_wrapper<const sf::Texture>>
    GetTexture(std::string_view name) const = 0;

    virtual const sf::Texture&
    RegisterTexture(std::string_view name, const sf::Texture&) = 0;

    virtual ~IResourceManager() {};
};

} // namespace OpenLabora

#endif // IRESOURCEMANAGER_HPP_
