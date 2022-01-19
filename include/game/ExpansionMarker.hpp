#ifndef EXPANSIONMARKER_HPP_
#define EXPANSIONMARKER_HPP_

#include <SFML/Graphics/ConvexShape.hpp>
#include "SelectableEntity.hpp"
#include "Plot.hpp"

namespace OpenLabora
{

class ExpansionMarker final
    : public SelectableEntity<sf::ConvexShape, sf::Sprite>
{
    inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };
    Plot mPlot;
    bool bMovesUp;
public:
    ExpansionMarker(const Plot&, bool moves_up = true);

    void OnHover() override;

    void OnOut() override;

    void Select(std::shared_ptr<AppStateManager>) override;

    bool IsPointInRegisteringArea(const sf::Vector2f& point) override
    { return mObject.getGlobalBounds().contains(point); }
};

} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
