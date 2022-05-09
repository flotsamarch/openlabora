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
    using RectangleArea = ClickableArea<sf::RectangleShape>;
    using GameControllerPtr = std::shared_ptr<GameController>;

    inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };
    Plot mPlot;
    Plot mPlotAlt;
    MarkerType mType;
    sf::RenderTexture mTexture;

public:
    ExpansionMarker(MarkerType,
                    const Plot& plot,
                    const Plot& plot_alt);

    bool IsPointInRegisteringArea(const sf::Vector2f& point) const override
    { return mClickableArea.GetGlobalBounds().contains(point); }

    Plot::PlotType GetPlotType() const noexcept { return mPlot.GetType(); }

    MarkerType GetType() const noexcept { return mType; }

    void Move(float offset_x, float offset_y) override;

    void Move(const sf::Vector2f& offset) override;

    void SetPosition(float position_x, float position_y) override;

    void SetPosition(const sf::Vector2f& position) override;

    void SetClickableArea(const sf::Vector2f& offset,
                          const sf::Vector2f& rect_size);

    void ResetClickableArea();

    std::pair<PlotRef, PlotRef> GetPlots() const
    { return { mPlot, mPlotAlt }; };
};

} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
