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

class Plot : public Entity
{
public:
    enum class PlotType
    {
        Coastal, Begin = Coastal, Central, Mountain, End
    };

    using TileSpanT = std::span<const Tile::TileType>;

    struct PlotTilesAndType
    {
        const TileSpanT tiles;
        const PlotType type;
    };

protected:
    static constexpr std::size_t kPlotTypeCount{ 3 };
    using PlotSizeArrayT = std::array<unsigned int, kPlotTypeCount>;
    static constexpr PlotSizeArrayT kPlotSizes{ 2, 5, 2 };

    template<PlotType type>
    struct PlotWidth
    {
        static constexpr auto w = kPlotSizes[static_cast<unsigned int>(type)];
    };

    using CentralPlotArrayT =
        std::array<Tile::TileType, PlotWidth<PlotType::Central>::w>;
    using CoastalPlotArrayT =
        std::array<Tile::TileType, PlotWidth<PlotType::Coastal>::w>;
    using MountainPlotArrayT =
        std::array<Tile::TileType, PlotWidth<PlotType::Mountain>::w>;

    std::vector<Tile> mTiles;
    std::shared_ptr<sf::RenderTexture> mPlotTexture;
    PlotType mType;

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

    void DrawTilesAsSprite();

    PlotType GetType() const noexcept { return mType; }

protected:
    static constexpr CoastalPlotArrayT kCoastalPlotTiles {
        Tile::TileType::Water, Tile::TileType::Coast
    };

    static constexpr CentralPlotArrayT kCentralPlotTopTiles {
        Tile::TileType::Peat,
        Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
        Tile::TileType::Hill
    };

    static constexpr CentralPlotArrayT kCentralPlotBottomTiles {
        Tile::TileType::Peat,
        Tile::TileType::Forest, Tile::TileType::Forest, Tile::TileType::Forest,
        Tile::TileType::Forest
    };

    static constexpr MountainPlotArrayT kMountainPlotTopTiles {
        Tile::TileType::Hill, Tile::TileType::Mountain
    };

    static constexpr MountainPlotArrayT kMountainPlotBottomTiles {
        Tile::TileType::Hill, Tile::TileType::None
    };

    static constexpr TileSpanT kCoastalPlotSpan{ kCoastalPlotTiles };
    static constexpr TileSpanT kCentralPlotTopSpan{ kCentralPlotTopTiles };
    static constexpr TileSpanT kCentralPlotBottomSpan{ kCentralPlotBottomTiles };
    static constexpr TileSpanT kMountainPlotTopSpan{ kMountainPlotTopTiles };
    static constexpr TileSpanT kMountainPlotBottomSpan{kMountainPlotBottomTiles};
public:
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

#endif // PLOT_HPP_
