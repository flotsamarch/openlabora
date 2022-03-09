#ifndef EXPANSIONMARKER_HPP_
#define EXPANSIONMARKER_HPP_

#include <optional>
#include <SFML/Graphics/RectangleShape.hpp>
#include "SelectableEntity.hpp"
#include "Plot.hpp"

namespace OpenLabora
{

class GameController;

class ExpansionMarker final
    : public SelectableEntity<sf::RectangleShape, sf::Sprite>
{
public:
    enum class MarkerType
    { Begin, Upper = Begin, Lower, Disposable, End, Max = End };

    using Ptr = std::shared_ptr<ExpansionMarker>;
    using WPtr = std::weak_ptr<ExpansionMarker>;

    static constexpr float kMarkerOverlapFactor = 1.f / 3.f;

private:
    using PlotRef = std::reference_wrapper<const Plot>;
    using OptionalPlot = std::optional<PlotRef>;
    using RectangleArea = ClickableArea<sf::RectangleShape>;
    using GameControllerPtr = std::shared_ptr<GameController>;

    inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };
    Plot mPlotTop;
    std::optional<Plot> mPlotBottom{ std::nullopt };
    MarkerType mType;
    sf::RenderTexture mTexture;

public:
    ExpansionMarker(MarkerType,
                    const Plot& top,
                    OptionalPlot bottom = std::nullopt);

    bool IsPointInRegisteringArea(const sf::Vector2f& point) const override
    { return mClickableArea.GetGlobalBounds().contains(point); }

    Plot::PlotType GetPlotType() const noexcept { return mPlotTop.GetType(); }

    MarkerType GetType() const noexcept { return mType; }

    void Move(float offset_x, float offset_y) override;

    void Move(const sf::Vector2f& offset) override;

    void SetPosition(float position_x, float position_y) override;

    void SetPosition(const sf::Vector2f& position) override;

    void SetClickableArea(const sf::Vector2f& offset,
                          const sf::Vector2f& rect_size);

    void ResetClickableArea();

    std::pair<PlotRef, OptionalPlot> GetPlots() const
    { return { mPlotTop, mPlotBottom }; };
};

} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
