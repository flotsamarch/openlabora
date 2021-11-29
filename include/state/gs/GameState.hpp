#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "state/gs/IGameState.hpp"

class State;

// General game logic base class
class GameState : public IGameState
{
protected:
    std::weak_ptr<State> mState;

public:
    GameState(std::shared_ptr<State> state) : mState{ state } {};

    virtual inline ~GameState() noexcept = 0;

    void HandleEvent(const sf::Event&) override {};

    void Update([[maybe_unused]]const float seconds) override {};
};

inline GameState::~GameState() noexcept {};

#endif // GAMESTATE_HPP_
