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
    static constexpr uint32_t kMaxFieldHeight{ 54u };
    static constexpr uint32_t kMaxFieldWidth{ 9u };
    static constexpr uint32_t kInitialPlotOffset{ 26u * Tile::kTileHeight };
    using Ptr = std::shared_ptr<Playfield>;

    Playfield(const IResourceManager&);

    Tile::TileInfo GetTileInfoUnderPoint(const sf::Vector2f&) const;

    void SetPosition(const sf::Vector2f&) override;

    void SetPosition(float offset_x, float offset_y) override;

    void AddPlotToTop(const Plot&);

    void AddPlotToBottom(const Plot&);

    // Returns positions for top and bottom expansion markers respectively for a
    // given plot type
    std::tuple<sf::Vector2f, sf::Vector2f>
    GetExpansionMarkerPositions(Plot::PlotType) const;

    bool IsPlotsLimitReached(Plot::PlotType) const;

    uint32_t GetDisposableMarkerCount(Plot::PlotType) const;

private:
    const IResourceManager& mResMgr;
    sf::RenderTexture mGroundTexture;
    std::map<Plot::PlotType, std::deque<Plot>> mPlots;

    void DrawPlotsAsSprite();

    std::optional<sf::Vector2u>
    GetTileIndicesUnderPoint(const sf::Vector2f&) const noexcept;

    inline static const std::map<Plot::PlotType, uint32_t> kMaxPlotCount =
    {
        { Plot::PlotType::Coastal, 18u },
        { Plot::PlotType::Central, 11u },
        { Plot::PlotType::Mountain, 18u }
    };
};

} // namespace OpenLabora

#endif // PLAYFIELD_HPP_
