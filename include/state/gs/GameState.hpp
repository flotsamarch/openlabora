#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <SFML/Window/Event.hpp>
#include "state/BaseState.hpp"

class GameState : public BaseState
{
public:
    GameState(State& state) : BaseState{ state } {};
    virtual ~GameState() override = default;
};


#endif // GAMESTATE_HPP_
