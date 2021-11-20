#ifndef BASESTATE_HPP_
#define BASESTATE_HPP_

#include <SFML/Window/Event.hpp>
#include <memory>
#include "IApplication.hpp"

class State;

class BaseState
{
protected:
    std::weak_ptr<State> mState;
public:
    BaseState(std::shared_ptr<State> state) : mState{ state } {};

    virtual inline ~BaseState() noexcept = 0;

    virtual void HandleEvent([[maybe_unused]]const sf::Event& evt) {};

    virtual void Update([[maybe_unused]]const float secondsSinceLastUpdate) {};
};

inline BaseState::~BaseState() noexcept {}

#endif // BASESTATE_HPP_
