#ifndef LANDPURCHASEMARKER_HPP_
#define LANDPURCHASEMARKER_HPP_

#include <SFML/Graphics/RectangleShape.hpp>
#include "SelectableEntity.hpp"
#include "ISelectable.hpp"

class LandPurchaseMarker final : public SelectableEntity
{
private:
    sf::RectangleShape& GetShape()
    {
        return static_cast<sf::RectangleShape&>(*mObject);
    }

    const sf::RectangleShape& GetShape() const
    {
        return static_cast<sf::RectangleShape&>(*mObject);
    }
public:
    LandPurchaseMarker(const sf::Vector2f& size);

    bool IsUnderPoint(const sf::Vector2f&) const noexcept override;

    void OnHover() override;

    void OnOut() override;

    const sf::Drawable& GetDrawableObject() const noexcept override
    {
        return static_cast<sf::RectangleShape&>(*mObject);
    };
};

#endif // LANDPURCHASEMARKER_HPP_
