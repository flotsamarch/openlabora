#ifndef LANDPURCHASEMARKER_HPP_
#define LANDPURCHASEMARKER_HPP_

#include <SFML/Graphics/ConvexShape.hpp>
#include "SelectableEntity.hpp"
#include "Plot.hpp"

class LandPurchaseMarker final : public SelectableEntity
{
    inline static const sf::Color kHalfTransparent{ 255, 255, 255, 200 };
    Plot mPlot;
    bool bMovesUp;
    // sf::FloatRect mClickableArea;
public:
    LandPurchaseMarker(const Plot&,
                       bool moves_up = true);

    void OnHover() override;

    void OnOut() override;

    void Select(std::shared_ptr<State>) override;

    // bool IsUnderPoint(const sf::Vector2f&) const override;
};

#endif // LANDPURCHASEMARKER_HPP_
