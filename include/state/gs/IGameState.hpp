#ifndef IGAMESTATE_HPP_
#define IGAMESTATE_HPP_

#include <vector>
#include "state/ILogicState.hpp"
#include "game/GameObject.hpp"

class IGameState : virtual public ILogicState
{
public:
    virtual ~IGameState() noexcept {};

    virtual GameObject::Iter GetGameObjectBegin() noexcept = 0;

    virtual GameObject::Iter GetGameObjectEnd() noexcept = 0;
};

#endif // IGAMESTATE_HPP_
