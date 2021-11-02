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
    virtual void HandleEvent(const sf::Event& evt) = 0;
    virtual void Update(const float secondsSinceLastUpdate) = 0;
    bool IsComplete() const { return bIsComplete; };
    bool ObjectsRequireUpdate() const { return bObjectsRequireUpdate; }
};

#endif // BASESTATE_HPP_
