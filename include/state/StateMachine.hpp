#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include "state/State.hpp"

class Application;

// Main game application state machine
class StateMachine final
{
    Application& mApp;
    State& mState;
public:
    StateMachine(Application& app, State& state) :
        mApp{ app }, mState{ state } {};
    ~StateMachine() = default;
    StateMachine(StateMachine&&) = delete;
    StateMachine& operator=(StateMachine&&) = delete;
    StateMachine(const StateMachine&) = delete;
    StateMachine& operator=(const StateMachine&) = delete;

    template <class TStatePair>
    void ChangeState();
};

template <class TStatePair>
void StateMachine::ChangeState()
{
    mState = State{TStatePair{}, mApp, mState};
}

#endif // STATE_MACHINE_HPP_
