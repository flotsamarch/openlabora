#ifndef IGAMESTATE_HPP_
#define IGAMESTATE_HPP_

#include "state/ILogicState.hpp"

class IGameState : virtual public ILogicState
{
public:
    virtual ~IGameState() noexcept {};
};

#endif // IGAMESTATE_HPP_
