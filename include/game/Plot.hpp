#ifndef PLOT_HPP_
#define PLOT_HPP_

#include <array>
#include <vector>
#include <span>
#include <memory>
#include <SFML/Graphics/RenderTexture.hpp>
#include "Tile.hpp"
#include "resource/IResourceManager.hpp"
#include "Entity.hpp"

namespace OpenLabora
{

class Plot : public Entity<sf::Sprite>
{
public:
    enum class PlotType
    { Coastal, Begin = Coastal, Central, Mountain, End };

    using TileSpan = std::span<const Tile::TileType>;

    struct PlotTilesAndType
    {
        const TileSpan tiles;
        const PlotType type;
    };

protected:
    static constexpr std::size_t kPlotTypeCount{ 3 };
    using PlotSizeArray = std::array<unsigned int, kPlotTypeCount>;

    static constexpr PlotSizeArray kPlotSizes{ 2, 5, 2 };

    template<PlotType type>
    struct PlotWidth
    { static constexpr auto w = kPlotSizes[static_cast<unsigned int>(type)]; };

    std::vector<Tile> mTiles;
    std::shared_ptr<sf::RenderTexture> mPlotTexture;
    PlotType mType;

    void DrawTilesAsSprite();

public:
    Plot(const PlotTilesAndType&,
         const IResourceManager&);
    virtual ~Plot() {};

    static unsigned int GetPlotWidthTileCount(PlotType type)
    {
        if (type == PlotType::End) {
            return 0;
        }
        return kPlotSizes[static_cast<int>(type)];
    }

    Tile::TileInfo GetTileInfoUnderPoint(const sf::Vector2f& point) const;

    PlotType GetType() const noexcept { return mType; }

protected:
    using CentralPlotArray =
        std::array<Tile::TileType, PlotWidth<PlotType::Central>::w>;
    using CoastalPlotArray =
        std::array<Tile::TileType, PlotWidth<PlotType::Coastal>::w>;
    using MountainPlotArray =
        std::array<Tile::TileType, PlotWidth<PlotType::Mountain>::w>;

    static constexpr CoastalPlotArray kCoastalPlotTiles
    { Tile::TileType::Water, Tile::TileType::Coast };

    static constexpr CentralPlotArray kCentralPlotTopTiles
    {
        Tile::TileType::Peat,
        Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
        Tile::TileType::Hill
    };

    static constexpr CentralPlotArray kCentralPlotBottomTiles
    {
        Tile::TileType::Peat,
        Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
        Tile::TileType::Forest
    };

    static constexpr MountainPlotArray kMountainPlotTopTiles
    { Tile::TileType::Hill, Tile::TileType::Mountain };

    static constexpr MountainPlotArray kMountainPlotBottomTiles
    { Tile::TileType::Hill, Tile::TileType::None };

    static constexpr TileSpan kCoastalPlotSpan{ kCoastalPlotTiles };
    static constexpr TileSpan kCentralPlotTopSpan{ kCentralPlotTopTiles };
    static constexpr TileSpan kCentralPlotBottomSpan{ kCentralPlotBottomTiles };
    static constexpr TileSpan kMountainPlotTopSpan{ kMountainPlotTopTiles };
    static constexpr TileSpan kMountainPlotBottomSpan{kMountainPlotBottomTiles};

public:
    // Defs for neat Plot object creation - constructor params packed in a struct
    static constexpr PlotTilesAndType kCostalPlot
        { kCoastalPlotSpan, PlotType::Coastal };
    static constexpr PlotTilesAndType kCentralPlotTop
        { kCentralPlotTopSpan, PlotType::Central };
    static constexpr PlotTilesAndType kCentralPlotBottom
        { kCentralPlotBottomSpan, PlotType::Central };
    static constexpr PlotTilesAndType kMountainPlotTop
        { kMountainPlotTopSpan, PlotType::Mountain };
    static constexpr PlotTilesAndType kMountainPlotBottom
        { kMountainPlotBottomSpan, PlotType::Mountain };
};

inline Plot::PlotType operator++ (Plot::PlotType& type) {
    if (type == Plot::PlotType::End) {
        return type;
    }
    type = static_cast<Plot::PlotType>(static_cast<int>(type) + 1);
    return type;
}

} // namespace OpenLabora

#endif // PLOT_HPP_