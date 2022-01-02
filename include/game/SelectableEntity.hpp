#ifndef SELECTABLEENTITY_HPP_
#define SELECTABLEENTITY_HPP_

#include "Entity.hpp"
#include "ISelectable.hpp"

class SelectableEntity : public Entity, public ISelectable
{
protected:
    bool bIsSelected;
    bool bWasEntered;

public:
    void Select() override { bIsSelected = true; }

    void Deselect() override { bIsSelected = false; }

    bool IsSelected() const noexcept override final { return bIsSelected; };
};

#endif // SELECTABLEENTITY_HPP_
