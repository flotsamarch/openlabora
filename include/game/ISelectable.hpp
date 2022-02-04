#ifndef ISELECTABLE_HPP_
#define ISELECTABLE_HPP_

#include <memory>
#include <SFML/System/Vector2.hpp>

namespace OpenLabora
{

class AppStateManager;

class ISelectable
{
public:
    using Ptr = std::shared_ptr<ISelectable>;
    using CPtr = std::shared_ptr<const ISelectable>;

    virtual ~ISelectable() noexcept {};

    virtual void OnHover() = 0;

    virtual void OnOut() = 0;

    virtual void Select() = 0;

    virtual void Deselect() = 0;

    virtual bool IsSelected() const noexcept = 0;

    virtual bool WasEntered() const noexcept = 0;

    // Test whether point is in area where a click should be registered
    // This takes global world coordinates
    virtual bool IsPointInRegisteringArea(const sf::Vector2f& point) const = 0;
};

} // namespace OpenLabora

#endif // ISELECTABLE_HPP_
