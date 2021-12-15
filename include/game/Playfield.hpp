#ifndef PLAYFIELD_HPP_
#define PLAYFIELD_HPP_

#include <array>
#include <SFML/Graphics/RenderTexture.hpp>
#include <optional>
#include "IDrawable.hpp"
#include "Location.hpp"
#include "Tile.hpp"

class Playfield final : public IDrawable
{
public:
    static constexpr unsigned int kFieldHeight{ 16 };
    static constexpr unsigned int kFieldWidth{ 9 };
    static constexpr unsigned int kTileHeight{ 150u };
    static constexpr unsigned int kTileWidth{ 100u };
    using LocationSubArray =
        std::array<std::unique_ptr<Location>, kFieldWidth>;
    using LocationArray = std::array<LocationSubArray, kFieldHeight>;
    using LocationIter = LocationSubArray::const_iterator;

    Playfield(const IResourceManager&);

    sf::Vector2f SnapPointToTile(const sf::Vector2f&) const noexcept;

    LocationIter GetLocationUnderPoint(const sf::Vector2f&);


    void ChangeLocationTypeAtPoint(const sf::Vector2f& point,
                                   Location::LocationType);

    constexpr LocationIter LocationsEnd() const noexcept
        { return mLocations.begin()->end(); };

    const sf::Sprite& GetSprite() const noexcept override
        { return mSprite; }
private:
    std::array<std::array<Tile::TileType, kFieldWidth>, kFieldHeight> mTiles;
    const IResourceManager& mResMgr;
    LocationArray mLocations;
    sf::RenderTexture mGroundTexture;
    sf::RenderTexture mLocationsTexture;
    sf::RenderTexture mTexture;
    sf::Sprite mSprite;

    bool IsTileValidForPlacement(const sf::Vector2u& indices,
                                 Location::LocationType) const;

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;

    LocationIter GetOrCreateLocationAt(const sf::Vector2u&,
                                       Location::LocationType =
                                       Location::LocationType::Empty);

    void DrawLocationOnFieldTexture(const Location&);
};

#endif // PLAYFIELD_HPP_
