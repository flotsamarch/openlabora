#ifndef SELECTABLE_ENTITY_HPP_
#define SELECTABLE_ENTITY_HPP_

#include "ISelectable.hpp"
#include "Entity.hpp"

class SelectableEntity : public Entity, public ISelectable
{
protected:
    bool bIsSelected;
    bool bWasEntered;

public:
    virtual ~SelectableEntity() noexcept = 0;

    void Select(std::shared_ptr<State>) override { bIsSelected = true; }

    void Deselect() override { bIsSelected = false; }

    bool IsSelected() const noexcept override final { return bIsSelected; };
};

inline SelectableEntity::~SelectableEntity() noexcept {};

#endif // SELECTABLE_ENTITY_HPP_
