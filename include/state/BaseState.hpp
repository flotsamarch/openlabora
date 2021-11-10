#ifndef BASESTATE_HPP_
#define BASESTATE_HPP_

#include <SFML/Window/Event.hpp>

class State;

class BaseState
{
protected:
    State& mState;
    bool bIsComplete{ false };
    bool bObjectsRequireUpdate{ true };
public:
    BaseState(State& state) : mState{ state } {};
    virtual ~BaseState() = default;
    virtual void HandleEvent([[maybe_unused]]const sf::Event& evt) {};
    virtual void Update([[maybe_unused]]const float secondsSinceLastUpdate) {};
    bool IsComplete() const { return bIsComplete; };
    bool ObjectsRequireUpdate() const { return bObjectsRequireUpdate; }
};

#endif // BASESTATE_HPP_
