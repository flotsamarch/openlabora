#ifndef EXPANSIONMARKER_HPP_
#define EXPANSIONMARKER_HPP_

#include <optional>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
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
    using PlotRef = std::reference_wrapper<const Plot>;
    using OptionalPlot = std::optional<PlotRef>;
    using RectangleArea = ClickableArea<sf::RectangleShape>;

    static constexpr float kMarkerOverlapFactor = 1.f / 3.f;

private:
    inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };
    Plot mPlotTop;
    std::optional<Plot> mPlotBottom{ std::nullopt };
    MarkerType mType;
    std::weak_ptr<sfg::Window> mWindow;
    std::weak_ptr<sfg::Button> mButton;
    uint32_t mSignalSerial{ 0u };
    sf::RenderTexture mTexture;

public:
    ExpansionMarker(std::shared_ptr<GameController>,
                    sfg::Window::Ptr, // Window that appears on click
                    sfg::Button::Ptr, // Creation confirm button
                    MarkerType,
                    const Plot& top,
                    OptionalPlot bottom = std::nullopt);

    ~ExpansionMarker();

    void OnHover() override;

    void OnOut() override;

    void Select() override;

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
};

} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
