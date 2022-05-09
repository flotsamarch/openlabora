// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef PLOT_HPP_
#define PLOT_HPP_

#include "ECS/ComponentContainer.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"
#include "Game/Components/PlotComponent.hpp"
#include "Resource/IResourceManager.hpp"

namespace OpenLabora
{

namespace plot
{

constexpr size_t kPlotTypeCount
{ static_cast<size_t>(plot::Type::End) - static_cast<size_t>(plot::Type::Begin)};

using Plot = ComponentContainer<PositionComponent,
                                PlotComponent,
                                SpriteComponent>;

constexpr std::array kCoastalPlotTiles
{ tile::Type::Water, tile::Type::Coast };

constexpr std::array kCentralPlotTiles
{
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Hill
};

constexpr std::array kCentralPlotAltTiles
{
    tile::Type::Peat,
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Hill, tile::Type::Hill
};

constexpr std::array kInitialCentralPlotTiles
{
    tile::Type::Peat, tile::Type::Forest,
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Hill
};

constexpr std::array kInitialCentralPlotAltTiles
{
    tile::Type::Peat,
    tile::Type::Forest, tile::Type::Forest,
    tile::Type::Forest, tile::Type::Forest
};

constexpr std::array kMountainPlotTopTiles
{ tile::Type::Hill, tile::Type::MountainUpper };

constexpr std::array kMountainPlotBottomTiles
{ tile::Type::Hill, tile::Type::MountainLower };

constexpr TileSpan kCoastalPlotSpan{ kCoastalPlotTiles };
constexpr TileSpan kCentralPlotSpan{ kCentralPlotTiles };
constexpr TileSpan kCentralPlotAltSpan{ kCentralPlotAltTiles };
constexpr TileSpan kMountainPlotTopSpan{ kMountainPlotTopTiles };
constexpr TileSpan kMountainPlotBottomSpan{kMountainPlotBottomTiles};

constexpr TileSpan kInitialCentralPlotSpan
{ kInitialCentralPlotTiles };
constexpr TileSpan kInitialCentralPlotAltSpan
{ kInitialCentralPlotAltTiles };

// ------------------- ADD TILE COUNT FOR EACH PLOT HERE ---------------------

constexpr EnumMap<Type, uint32_t> kPlotWidthTileCount
{
    { Type::Coastal, 2u },
    { Type::Central, 5u },
    { Type::Mountain, 2u },
};

// ------------------- ADD MAXIMUM COUNT OF EACH PLOT HERE ---------------------

constexpr EnumMap<Type, uint32_t> kPlotMaxCount
{
    { Type::Coastal, 18u },
    { Type::Central, 11u },
    { Type::Mountain, 18u },
};

// -------------------- ADD TEXTURE ID FOR EACH PLOT HERE ----------------------

constexpr std::string_view kCoastalTextureName = "coastal_plot";
constexpr std::string_view kCentralTextureName = "central_plot";
constexpr std::string_view kCentralAltTextureName = "central_plot_alt";
constexpr std::string_view kMountainTextureName = "mountain_plot";
constexpr std::string_view kMountainAltTextureName = "mountain_plot_alt";
constexpr std::string_view kCentralInitTextureName = "central_init_plot";
constexpr std::string_view kCentralInitAltTextureName = "central_init_plot_alt";

using TextureIdMapValueType = std::pair<std::string_view, std::string_view>;
constexpr EnumMap<Type, TextureIdMapValueType> kTextureIdMap
{
    { Type::Coastal, { kCoastalTextureName, kCoastalTextureName } },
    { Type::Central, { kCentralTextureName, kCentralAltTextureName } },
    { Type::Mountain, { kMountainTextureName, kMountainAltTextureName } },
};

// --------------------- ADD SPANS FOR EACH PLOT TYPE HERE ---------------------
constexpr EnumMap<Type, std::pair<TileSpan, TileSpan>> kPlotTypeToSpans
{
    { Type::Coastal, { kCoastalPlotSpan, kCentralPlotAltSpan } },
    { Type::Central, { kCentralPlotSpan, kCentralPlotAltSpan } },
    { Type::Mountain, {kMountainPlotTopSpan, kMountainPlotBottomSpan } },
};

// Use to create plots during gameplay
Plot create(Type type, const sf::Vector2f& position,
            IResourceManager::Ptr, bool alternative = false);

// NOT the same as create(Type::Coastal, ...) - Uses special spans
Plot createCentralInitial(const sf::Vector2f& position,
                          IResourceManager::Ptr,
                          bool alternative = false);

} // namespace plot

} // namespace OpenLabora

#endif // PLOT_HPP_
