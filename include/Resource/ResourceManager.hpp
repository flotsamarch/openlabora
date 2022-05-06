#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <unordered_map>
#include <filesystem>
#include "IResourceManager.hpp"

namespace OpenLabora
{

class ResourceManager final : public IResourceManager
{
    std::unordered_map<std::string, sf::Texture> mTextures;

    static constexpr auto kLoadErrorFormat =
        std::string_view{ "Unable to load texture from file: {}" };

    static constexpr auto kMalformedCommandLine =
        std::string_view{ "Malformed command line arguments" };

    static constexpr auto kNoResourceDirectory =
        std::string_view{ "Unable to find resource directory" };

    static constexpr auto kResourceDirectoryName = std::string_view{ "res/" };

public:
    ResourceManager(const std::filesystem::path&);

    const sf::Texture&
    GetTextureOrDefault(std::string_view name) const override;

    std::optional<std::reference_wrapper<const sf::Texture>>
    GetTexture(std::string_view) const override;

    const sf::Texture&
    RegisterTexture(std::string_view name, const sf::Texture&) override;
};

} // namespace OpenLabora

#endif // RESOURCEMANAGER_HPP_
