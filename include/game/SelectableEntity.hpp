#ifndef SELECTABLE_ENTITY_HPP_
#define SELECTABLE_ENTITY_HPP_

#include "ISelectable.hpp"
#include "Entity.hpp"
#include "GUI/ClickableArea.hpp"

namespace OpenLabora
{

template<class TShape, SFCombined U>
requires std::is_base_of<sf::Shape, TShape>::value
class SelectableEntity : public Entity<U>, public ISelectable
{
protected:
    bool bSelected{ false };
    bool bEntered{ false };
    ClickableArea<TShape> mClickableArea;

public:
    virtual ~SelectableEntity() noexcept {};

    void Select() override
    { bSelected = true; }

    void Deselect() override { bSelected = false; }

    bool IsSelected() const noexcept override final { return bSelected; }

    bool WasEntered() const noexcept override final { return bEntered; }

    void SetClickableArea(const TShape& area) { mClickableArea = area; }
};

} // namespace OpenLabora

#endif // SELECTABLE_ENTITY_HPP_
