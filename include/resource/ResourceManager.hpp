#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <cassert>
#include <unordered_map>
#include "IResourceManager.hpp"

class ResourceManager final : public IResourceManager
{
    std::unordered_map<std::string_view, sf::Texture> mTextures;
public:
    const sf::Texture& GetTextureByName(std::string_view name) const override
    {
        auto res = mTextures.find(name);
        if (res == mTextures.end()) {
            return mTextures.find("coin")->second;
        }
        return mTextures.find(name)->second;
    }

    ResourceManager()
    {
        mTextures["coin"].loadFromFile("res\\coin.png");
        mTextures["forest"].loadFromFile("res\\forest.png");
        mTextures["location"].loadFromFile("res\\location.png");
    }
};

#endif // RESOURCEMANAGER_HPP_
