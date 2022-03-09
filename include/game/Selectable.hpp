#ifndef SELECTABLE_HPP_
#define SELECTABLE_HPP_

#include <functional>
#include <memory>
#include <SFML/System/Vector2.hpp>

namespace OpenLabora
{

class AppStateManager;

class Selectable
{
protected:
    bool bSelected{ false };
    bool bEntered{ false };
    // TODO Please purge this abomination out of this class
    std::function<void()> mSelectDelegate;
    std::function<void()> mDeselectDelegate;
    std::function<void()> mHoverDelegate;
    std::function<void()> mOutDelegate;
public:
    using Ptr = std::shared_ptr<Selectable>;
    using CPtr = std::shared_ptr<const Selectable>;

    virtual ~Selectable() {};

    void OnHover()
    {
        if (!bEntered) {
            bEntered = true;
            if (mHoverDelegate)
                mHoverDelegate();
        }
    }

    void OnOut()
    {
        if (bEntered) {
            bEntered = false;
            if (mOutDelegate)
                mOutDelegate();
        }
    }

    void Select()
    {
        if (!bSelected) {
            bSelected = true;
            if (mSelectDelegate)
                mSelectDelegate();
        }
    }

    void Deselect()
    {
        if (bSelected) {
            bSelected = false;
            if (mDeselectDelegate)
                mDeselectDelegate();
        }
    }

    bool IsSelected() const noexcept { return bSelected; }

    bool WasEntered() const noexcept { return bEntered; }

    // Test whether point is in area where a click should be registered
    // This takes global world coordinates
    virtual bool IsPointInRegisteringArea(const sf::Vector2f& point) const = 0;
};

} // namespace OpenLabora

#endif // SELECTABLE_HPP_
