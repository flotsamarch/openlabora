#include "game/LandPurchaseMarker.hpp"

LandPurchaseMarker::LandPurchaseMarker(const sf::Vector2f& size)
{
    mObject = std::make_unique<sf::RectangleShape>(size);
    auto&& shape = GetShape();
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Transparent);
    shape.setOutlineThickness(5);
}

bool LandPurchaseMarker::IsUnderPoint(const sf::Vector2f& point) const noexcept
{
    return GetShape().getGlobalBounds().contains(point);
}

void LandPurchaseMarker::OnHover()
{
    if (bWasEntered) {
        return;
    }

    bWasEntered = true;

    GetShape().setOutlineColor(sf::Color::Yellow);
}

void LandPurchaseMarker::OnOut()
{
    if (!bWasEntered) {
        return;
    }

    bWasEntered = false;

    GetShape().setOutlineColor(sf::Color::Transparent);
}
