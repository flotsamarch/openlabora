#ifndef IGAMESTATE_HPP_
#define IGAMESTATE_HPP_

#include <vector>
#include "state/ILogicState.hpp"
#include "game/IDrawable.hpp"

class IGameState : virtual public ILogicState
{
public:
    virtual ~IGameState() noexcept = 0;

    virtual void SetPaused(bool) noexcept = 0;

    virtual bool IsPaused() noexcept = 0;

    virtual IDrawable::Iter GetGameObjectBegin() noexcept = 0;

    virtual IDrawable::Iter GetGameObjectEnd() noexcept = 0;
};

inline IGameState::~IGameState() noexcept {};

#endif // IGAMESTATE_HPP_
