#ifndef GAMEOBJECT_HPP_
#define GAMEOBJECT_HPP_

#include <memory>
#include "game/IDrawable.hpp"
#include "game/IMovable.hpp"
#include "resource/IResourceManager.hpp"

class GameObject : public IDrawable, public IMovable
{
protected:
    static constexpr std::string_view kTextureName{ "coin" };
    sf::Sprite mSprite;
    const IResourceManager& mResMgr;
public:
    inline static const sf::Vector2f kOutOfBounds{ -999999.f, -999999.f };

    GameObject(const IResourceManager& res_mgr,
               std::string_view texture_name = kTextureName) :
        mResMgr{ res_mgr }
    {
        mSprite.setTexture(mResMgr.GetTextureByName(texture_name));
    }

    virtual void Move(float offset_x, float offset_y) override
    {
        mSprite.move(offset_x, offset_y);
    }

    virtual void Move(const sf::Vector2f& offset) override
    {
        mSprite.move(offset);
    }

    virtual void SetPosition(float offset_x, float offset_y) override
    {
        mSprite.setPosition(offset_x, offset_y);
    }

    virtual void SetPosition(const sf::Vector2f& offset) override
    {
        mSprite.setPosition(offset);
    }

    sf::Vector2f GetPosition() override
    {
        return mSprite.getPosition();
    }

    inline virtual ~GameObject() noexcept = 0;

    virtual const sf::Sprite& GetSprite() const noexcept override
    {
        return mSprite;
    }
};

inline GameObject::~GameObject() noexcept {};

#endif // GAMEOBJECT_HPP_
