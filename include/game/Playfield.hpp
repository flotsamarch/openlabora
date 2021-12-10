#ifndef PLAYFIELD_HPP_
#define PLAYFIELD_HPP_

#include <array>
#include <SFML/Graphics/RenderTexture.hpp>
#include <optional>
#include "GameObject.hpp"
#include "Location.hpp"
#include "Tile.hpp"

class Playfield final : public GameObject
{
public:
    static constexpr unsigned int kFieldHeight{ 16 };
    static constexpr unsigned int kFieldWidth{ 12 };
    static constexpr unsigned int kTileHeight{ 150u };
    static constexpr unsigned int kTileWidth{ 100u };
    using LocationSubArray =
        std::array<std::unique_ptr<Location>, kFieldWidth>;
    using LocationArray = std::array<LocationSubArray, kFieldHeight>;
    using LocationIter = LocationSubArray::const_iterator;

    Playfield(const IResourceManager&);

    sf::Vector2f SnapPointToTile(const sf::Vector2f&) const noexcept;

    LocationIter GetLocationUnderPoint(const sf::Vector2f&) const;


    void CreateLocationAtPoint(const sf::Vector2f& point,
                               Location::LocationType,
                               const IResourceManager&);

    constexpr LocationIter LocationsEnd() noexcept
        { return mLocations.begin()->end(); };
private:
    std::array<std::array<Tile::TileType, kFieldWidth>, kFieldHeight> mTiles;
    sf::RenderTexture mFieldTexture;
    LocationArray mLocations;

    bool IsTileValidForPlacement(const sf::Vector2u& indices,
                                 Location::LocationType) const;

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;

    LocationIter GetLocationAt(const sf::Vector2u&) const;

    void DrawLocationOnFieldTexture(const Location&);
};

#endif // PLAYFIELD_HPP_
