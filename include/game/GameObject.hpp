#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include "resource/IResourceManager.hpp"

class GameObject
{
protected:
    static constexpr std::string_view kTextureName{ "coin" };
    sf::Sprite mSprite;
public:
    using UPtr = std::unique_ptr<GameObject>;
    using Iter = std::vector<UPtr>::iterator;
    inline static const sf::Vector2f kOutOfBounds{ -999999.f, -999999.f };

    GameObject(const IResourceManager& res_mgr,
               std::string_view texture_name = kTextureName)
    {
        mSprite.setTexture(res_mgr.GetTextureByName(texture_name));
    }

    virtual void Move(float offset_x, float offset_y)
    {
        mSprite.move(offset_x, offset_y);
    }

    virtual void Move(const sf::Vector2f& offset)
    {
        mSprite.move(offset);
    }

    virtual void SetPosition(float offset_x, float offset_y)
    {
        mSprite.setPosition(offset_x, offset_y);
    }

    virtual void SetPosition(const sf::Vector2f& offset)
    {
        mSprite.setPosition(offset);
    }

    inline virtual ~GameObject() noexcept = 0;

    virtual const sf::Sprite& GetSprite() const { return mSprite; }
};

inline GameObject::~GameObject() noexcept {};

#endif // GAMEOBJECT_HPP_
