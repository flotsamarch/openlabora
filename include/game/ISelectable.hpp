#ifndef ISELECTABLE_HPP_
#define ISELECTABLE_HPP_

#include "SFML/System/Vector2.hpp"

class ISelectable
{
public:
    virtual ~ISelectable() noexcept {};

    virtual bool IsUnderPoint(const sf::Vector2f&) const noexcept = 0;

    virtual void OnHover() = 0;

    virtual void OnOut() = 0;

    virtual void Select() = 0;

    virtual void Deselect() = 0;

    virtual bool IsSelected() const noexcept = 0;
};

#endif // ISELECTABLE_HPP_
