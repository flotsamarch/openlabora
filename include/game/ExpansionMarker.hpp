#ifndef EXPANSIONMARKER_HPP_
#define EXPANSIONMARKER_HPP_

#include <SFML/Graphics/ConvexShape.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include "SelectableEntity.hpp"
#include "Plot.hpp"

namespace OpenLabora
{

class Playfield;

class ExpansionMarker final
    : public SelectableEntity<sf::ConvexShape, sf::Sprite>
{
public:
    enum class MarkerType
    { Begin, Upper = Begin, Lower, Disposable, End, Max = End };

    using Ptr = std::shared_ptr<ExpansionMarker>;

private:
    inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };
    Plot mPlot;
    MarkerType mType;
    std::weak_ptr<sfg::Window> mWindow;
    std::weak_ptr<sfg::Button> mButton;
    uint32_t mSignalSerial{ 0u };

public:
    ExpansionMarker(const Plot&,
                    MarkerType,
                    std::shared_ptr<Playfield>,
                    std::shared_ptr<sfg::Window>, // Window that appears on click
                    std::shared_ptr<sfg::Button>); // Creation confirm button
    ~ExpansionMarker();

    void OnHover() override;

    void OnOut() override;

    void Select() override;

    bool IsPointInRegisteringArea(const sf::Vector2f& point) const override
    { return mObject.getGlobalBounds().contains(point); }

    Plot::PlotType GetPlotType() const noexcept
    { return mPlot.GetType(); }

    MarkerType GetType() const noexcept
    { return mType; }
};

} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
