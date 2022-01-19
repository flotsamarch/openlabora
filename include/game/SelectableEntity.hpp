#ifndef SELECTABLE_ENTITY_HPP_
#define SELECTABLE_ENTITY_HPP_

#include "ISelectable.hpp"
#include "Entity.hpp"

namespace OpenLabora
{

template<class TShape, SFCombined U>
requires std::is_base_of<sf::Shape, TShape>::value
class SelectableEntity : public Entity<U>, public ISelectable
{
protected:
    bool bIsSelected;
    bool bWasEntered;
    TShape mClickableArea;

public:
    virtual ~SelectableEntity() noexcept {};

    void Select(std::shared_ptr<AppStateManager>) override
    { bIsSelected = true; }

    void Deselect() override { bIsSelected = false; }

    bool IsSelected() const noexcept override final { return bIsSelected; }

    bool WasEntered() const noexcept override final { return bWasEntered; }
};

} // namespace OpenLabora

#endif // SELECTABLE_ENTITY_HPP_
