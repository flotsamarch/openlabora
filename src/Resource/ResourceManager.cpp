#include <cassert>
#include <filesystem>
#include <iostream>
#include <sstream>
#include "Resource/ResourceManager.hpp"

namespace OpenLabora
{

ResourceManager::ResourceManager()
{
    auto dir = std::filesystem::directory_entry("res/");
    auto suffix = std::string_view(".png");

    assert(dir.is_directory());

    for (auto&& file : std::filesystem::directory_iterator{dir}) {
        if (!file.is_regular_file()) {
            continue;
        }
        const auto&& path = file.path().string();
        if (path.substr(path.size() - suffix.size()) == suffix) {
            const auto&& filename = file.path().filename().string();
            auto texture_name =
                filename.substr(0, filename.size() - suffix.size());
            auto texture = sf::Texture{};
            if (!texture.loadFromFile(file.path().string())) {
                // TODO: Exception safety pass
                auto message = std::stringstream{kLoadErrorFormat.data()};
                message << filename;
                throw std::runtime_error{ message.str() };
            }
            mTextures[texture_name] = texture;
        }
    }
}

std::optional<std::reference_wrapper<const sf::Texture>>
ResourceManager::GetTexture(std::string_view name) const
{
    auto str = std::string{ name };
    auto&& result = mTextures.find(str);

    if (result == mTextures.end()) {
        return {};
    }

    return { mTextures.find(str)->second };
}

const sf::Texture&
ResourceManager::GetTextureOrDefault(std::string_view name) const
{
    auto str = std::string{ name };
    auto&& result = mTextures.find(str);

    if (result == mTextures.end()) {
        return mTextures.find("coin")->second;
    }
    return mTextures.find(str)->second;
}

const sf::Texture& ResourceManager::RegisterTexture(std::string_view name,
                                                    const sf::Texture& texture)
{
    auto result = mTextures.emplace(std::make_pair(name, texture));
    assert(result.second);
    return result.first->second;
};

} // namespace OpenLabora
