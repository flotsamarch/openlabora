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
        mTextures["coast"].loadFromFile("res\\coast.png");
        mTextures["water"].loadFromFile("res\\water.png");
        mTextures["peat_empty"].loadFromFile("res\\peat_empty.png");
        mTextures["peat"].loadFromFile("res\\peat.png");
        mTextures["hill"].loadFromFile("res\\hill.png");
        mTextures["mountain"].loadFromFile("res\\mountain.png");
        mTextures["location"].loadFromFile("res\\location.png");
        mTextures["fishing"].loadFromFile("res\\fishing.png");
        mTextures["claymound"].loadFromFile("res\\claymound.png");
        mTextures["houseboat"].loadFromFile("res\\houseboat.png");
    }
};

#endif // RESOURCEMANAGER_HPP_
