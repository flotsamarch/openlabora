#ifndef PLAYFIELD_HPP_
#define PLAYFIELD_HPP_

#include <array>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include "IDrawable.hpp"
#include "Entity.hpp"

class Playfield final : public Entity
{
public:
    enum class TileType
    {
        None, Begin = None, Forest,
        Hill, Mountain, Water, Coast,
        Peat, End
    };

    struct TileInfo
    {
        sf::Vector2u indices{ 0u, 0u };
        sf::Vector2f coord{ 0.f, 0.f };
        TileType type{ TileType::None };
    };

    static constexpr unsigned int kFieldHeight{ 8 };
    static constexpr unsigned int kFieldWidth{ 9 };
    static constexpr unsigned int kTileHeight{ 150u };
    static constexpr unsigned int kTileWidth{ 100u };

    // TODO make constexpr with latest SFML ver.
    inline static const TileInfo kBadTile
    {
        sf::Vector2u{ 0u, 0u },
        sf::Vector2f{ 0.f, 0.f },
        TileType{ TileType::None }
    };

    Playfield(const IResourceManager&);

    const sf::Drawable& GetDrawableObject() const noexcept override
    { return *static_cast<sf::Sprite*>(mObject.get()); }

    TileInfo GetTileInfoUnderPoint(const sf::Vector2f&) const;
private:
    std::array<std::array<TileType, kFieldWidth>, kFieldHeight> mTiles;
    const IResourceManager& mResMgr;
    sf::RenderTexture mGroundTexture;
    sf::RenderTexture mTexture;

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;

    virtual void Move(float, float) override {};

    virtual void Move(const sf::Vector2f&) override {};

    virtual void SetPosition(float, float) override {};

    virtual void SetPosition(const sf::Vector2f&) override {};
};

inline Playfield::TileType operator++ (Playfield::TileType& type) {
    if (type == Playfield::TileType::End) {
        return type;
    }
    type = static_cast<Playfield::TileType>(static_cast<int>(type) + 1);
    return type;
}

bool operator==(const Playfield::TileInfo& lhs,
                const Playfield::TileInfo& rhs);

#endif // PLAYFIELD_HPP_
