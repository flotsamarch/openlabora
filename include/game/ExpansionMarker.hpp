#ifndef EXPANSIONMARKER_HPP_
#define EXPANSIONMARKER_HPP_

#include <optional>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include "SelectableEntity.hpp"
#include "Plot.hpp"

namespace OpenLabora
{

class GameController;

class ExpansionMarker final
    : public SelectableEntity<sf::ConvexShape, sf::Sprite>
{
public:
    enum class MarkerType
    { Begin, Upper = Begin, Lower, Disposable, End, Max = End };

    using Ptr = std::shared_ptr<ExpansionMarker>;
    using PlotRef = std::reference_wrapper<Plot>;

private:
    inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };
    Plot mPlotTop;
    std::optional<Plot> mPlotBottom{ std::nullopt };
    MarkerType mType;
    std::weak_ptr<sfg::Window> mWindow;
    std::weak_ptr<sfg::Button> mButton;
    uint32_t mSignalSerial{ 0u };

public:
    ExpansionMarker(std::shared_ptr<GameController>,
                    sfg::Window::Ptr, // Window that appears on click
                    sfg::Button::Ptr, // Creation confirm button
                    MarkerType,
                    const Plot& top);

    ExpansionMarker(std::shared_ptr<GameController>,
                    sfg::Window::Ptr, // Window that appears on click
                    sfg::Button::Ptr, // Creation confirm button
                    MarkerType,
                    const Plot& top,
                    const Plot& bottom);

    ~ExpansionMarker();

    void OnHover() override;

    void OnOut() override;

    void Select() override;

    bool IsPointInRegisteringArea(const sf::Vector2f& point) const override
    { return mObject.getGlobalBounds().contains(point); }

    Plot::PlotType GetPlotType() const noexcept
    { return mPlotTop.GetType(); }

    MarkerType GetType() const noexcept
    { return mType; }
};

} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
