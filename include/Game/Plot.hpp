#ifndef PLOT_HPP_
#define PLOT_HPP_

#include <array>
#include <vector>
#include <span>
#include <memory>
#include <optional>
#include <SFML/Graphics/RenderTexture.hpp>
#include "Tile.hpp"
#include "Resource/IResourceManager.hpp"
#include "Entity.hpp"

namespace OpenLabora
{

class Plot : public Entity<sf::Sprite>
{
public:
    enum class PlotType
    { Begin, Coastal = Begin, Central, Mountain, End };

    using TileSpan = std::span<const Tile::TileType>;
    using Ptr = std::shared_ptr<Plot>;
    using OptionalTileInfo = std::optional<Tile::TileInfo>;

    struct PlotTilesAndType
    {
        const TileSpan tiles;
        const PlotType type;
    };

protected:
    static constexpr size_t kPlotTypeCount{ 3 };
    using PlotSizeArray = std::array<uint32_t, kPlotTypeCount>;

    static constexpr PlotSizeArray kPlotSizes{ 2u, 5u, 2u };

    template<PlotType type>
    struct PlotWidth
    { static constexpr auto w = kPlotSizes[static_cast<size_t>(type)]; };

    std::vector<Tile> mTiles;
    std::shared_ptr<sf::RenderTexture> mPlotTexture;
    PlotType mType;

    void DrawTilesAsSprite();

public:
    Plot(const PlotTilesAndType&,
         IResourceManager::Ptr);
    virtual ~Plot() {};

    static uint32_t GetPlotWidthTileCount(PlotType);

    static float GetOffsetXForPlotType(PlotType);

    OptionalTileInfo GetTileInfoUnderPoint(const sf::Vector2f& point) const;

    PlotType GetType() const noexcept { return mType; }

    uint32_t GetTileCount() const noexcept
    { return static_cast<uint32_t>(mTiles.size()); }

protected:
    using CentralPlotArray =
        std::array<Tile::TileType, PlotWidth<PlotType::Central>::w>;
    using CoastalPlotArray =
        std::array<Tile::TileType, PlotWidth<PlotType::Coastal>::w>;
    using MountainPlotArray =
        std::array<Tile::TileType, PlotWidth<PlotType::Mountain>::w>;

    static constexpr CoastalPlotArray kCoastalPlotTiles
    { Tile::TileType::Water, Tile::TileType::Coast };

    static constexpr CentralPlotArray kCentralPlotTiles
    {
        Tile::TileType::Peat,
        Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
        Tile::TileType::Hill
    };

    static constexpr CentralPlotArray kCentralPlotAltTiles
    {
        Tile::TileType::Peat,
        Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
        Tile::TileType::Forest
    };

    static constexpr MountainPlotArray kMountainPlotTopTiles
    { Tile::TileType::Hill, Tile::TileType::MountainUpper };

    static constexpr MountainPlotArray kMountainPlotBottomTiles
    { Tile::TileType::Hill, Tile::TileType::MountainLower };

    static constexpr TileSpan kCoastalPlotSpan{ kCoastalPlotTiles };
    static constexpr TileSpan kCentralPlotSpan{ kCentralPlotTiles };
    static constexpr TileSpan kCentralPlotAltSpan{ kCentralPlotAltTiles };
    static constexpr TileSpan kMountainPlotTopSpan{ kMountainPlotTopTiles };
    static constexpr TileSpan kMountainPlotBottomSpan{kMountainPlotBottomTiles};

public:
    // Defs for neat Plot object creation - constructor params packed in a struct
    static constexpr PlotTilesAndType kCostalPlot
        { kCoastalPlotSpan, PlotType::Coastal };
    static constexpr PlotTilesAndType kCentralPlot
        { kCentralPlotSpan, PlotType::Central };
    static constexpr PlotTilesAndType kCentralPlotAlt
        { kCentralPlotAltSpan, PlotType::Central };
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
