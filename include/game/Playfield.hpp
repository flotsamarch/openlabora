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

class Playfield final : public Entity
{
public:
    static constexpr unsigned int kFieldHeight{ 8 };
    static constexpr unsigned int kFieldWidth{ 9 };

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

    // Returns y coordinates of top and bottom edges of owned lands by plot type
    std::tuple<float, float> GetLandTopAndBottomEdges(Plot::PlotType) const;
private:
    const IResourceManager& mResMgr;
    sf::RenderTexture mGroundTexture;
    std::map<Plot::PlotType, std::deque<Plot>> mPlots;

    void DrawPlotsAsSprite();

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;

    using Entity::Move;
    using Entity::SetPosition;
};

#endif // PLAYFIELD_HPP_
