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

namespace OpenLabora
{

class Playfield final : public Entity<sf::Sprite>
{
public:
    static constexpr unsigned int kMaxFieldHeight{ 8 };
    static constexpr unsigned int kMaxFieldWidth{ 9 };

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
private:
    const IResourceManager& mResMgr;
    sf::RenderTexture mGroundTexture;
    std::map<Plot::PlotType, std::deque<Plot>> mPlots;

    void DrawPlotsAsSprite();

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;
};

} // namespace OpenLabora

#endif // PLAYFIELD_HPP_
