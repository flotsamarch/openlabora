#ifndef BASESTATE_HPP_
#define BASESTATE_HPP_

#include <SFML/Window/Event.hpp>

class State;

class BaseState
{
protected:
    State& mState;
public:
    BaseState(State& state) : mState{ state } {};
    virtual ~BaseState() = default;
    virtual void HandleEvent([[maybe_unused]]const sf::Event& evt) {};
    virtual void Update([[maybe_unused]]const float secondsSinceLastUpdate) {};
};

#endif // BASESTATE_HPP_
