#ifndef PLAYFIELD_HPP_
#define PLAYFIELD_HPP_

#include <array>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <optional>
#include <deque>
#include <map>
#include <tuple>
#include "Plot.hpp"
#include "IDrawable.hpp"
#include "Entity.hpp"
#include "Tile.hpp"
#include "ExpansionMarker.hpp"

namespace OpenLabora
{

class Playfield final : public Entity<sf::Sprite>
{
public:
    static constexpr uint32_t kMaxFieldHeight{ 36 };
    static constexpr uint32_t kMaxFieldWidth{ 9 };
    static constexpr uint32_t kInitialPlotOffset{ 17 * Tile::kTileHeight };

    Playfield(const IResourceManager&);

    Tile::TileInfo GetTileInfoUnderPoint(const sf::Vector2f&) const;

    void PushPlotBack(const Plot& plot)
    {
        mPlots[plot.GetType()].push_back(plot);
        DrawPlotsAsSprite();
    }

    void PushPlotFront(const Plot& plot)
    {
        mPlots[plot.GetType()].push_front(plot);
        DrawPlotsAsSprite();
    }

    // Returns positions for top and bottom expansion markers respectively for a
    // given plot type
    std::tuple<sf::Vector2f, sf::Vector2f>
    GetExpansionMarkerPositions(Plot::PlotType) const;

    bool IsPlotsLimitReached(Plot::PlotType, ExpansionMarker::MarkerType);
private:
    const IResourceManager& mResMgr;
    sf::RenderTexture mGroundTexture;
    std::map<Plot::PlotType, std::deque<Plot>> mPlots;

    void DrawPlotsAsSprite();

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;

    inline static const std::map<Plot::PlotType, uint32_t> kMaxPlotCount =
    {
        { Plot::PlotType::Coastal, 9u },
        { Plot::PlotType::Central, 11u },
        { Plot::PlotType::Mountain, 9u }
    };
};

} // namespace OpenLabora

#endif // PLAYFIELD_HPP_
