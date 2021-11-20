#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <SFML/Window/Event.hpp>
#include "state/BaseState.hpp"

// General game logic base class
class GameState : public BaseState
{
public:
    GameState(std::shared_ptr<State> state) : BaseState{ state } {};
};


#endif // GAMESTATE_HPP_
