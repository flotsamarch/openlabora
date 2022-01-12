#ifndef ISELECTABLE_HPP_
#define ISELECTABLE_HPP_

#include <SFML/System/Vector2.hpp>
#include "state/ui/IUiState.hpp"

class ISelectable
{
public:
    virtual ~ISelectable() noexcept {};

    virtual void OnHover() = 0;

    virtual void OnOut() = 0;

    virtual void Select(IUiState&) = 0;

    virtual void Deselect() = 0;

    virtual bool IsSelected() const noexcept = 0;
};

#endif // ISELECTABLE_HPP_
