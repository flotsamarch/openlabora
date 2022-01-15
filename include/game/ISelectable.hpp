#ifndef ISELECTABLE_HPP_
#define ISELECTABLE_HPP_

#include <memory>
#include <SFML/System/Vector2.hpp>
#include "state/ui/IUiState.hpp"

class State;

class ISelectable
{
public:
    virtual ~ISelectable() noexcept {};

    virtual void OnHover() = 0;

    virtual void OnOut() = 0;

    virtual void Select(std::shared_ptr<State>) = 0;

    virtual void Deselect() = 0;

    virtual bool IsSelected() const noexcept = 0;
};

#endif // ISELECTABLE_HPP_
