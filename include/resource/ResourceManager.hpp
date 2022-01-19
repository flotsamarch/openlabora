#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <cassert>
#include <unordered_map>
#include <filesystem>
#include <iostream>
#include "IResourceManager.hpp"

namespace OpenLabora
{

class ResourceManager final : public IResourceManager
{
    std::unordered_map<std::string, sf::Texture> mTextures;
public:
    const sf::Texture& GetTextureByName(std::string_view name) const override
    {
        auto str = std::string{name};
        auto res = mTextures.find(str);

        if (res == mTextures.end()) {
            return mTextures.find("coin")->second;
        }
        return mTextures.find(str)->second;
    }

    ResourceManager()
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
                mTextures[texture_name].loadFromFile(file.path().string());
            }
        }
    }
};

} // namespace OpenLabora

#endif // RESOURCEMANAGER_HPP_
