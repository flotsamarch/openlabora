#ifndef IRESOURCEMANAGER_HPP_
#define IRESOURCEMANAGER_HPP_

#include <string_view>
#include <SFML/Graphics/Texture.hpp>

namespace OpenLabora
{

class IResourceManager
{
public:
    virtual const sf::Texture& GetTextureByName(std::string_view) const = 0;

    virtual ~IResourceManager() {};
};

} // namespace OpenLabora

#endif // IRESOURCEMANAGER_HPP_
