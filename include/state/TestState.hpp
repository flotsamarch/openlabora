#ifndef TESTSTATE_HPP_
#define TESTSTATE_HPP_

#include <state/GameState.hpp>

class TestState final : public GameState
{
public:
    TestState() = default;
    virtual ~TestState() override final = default;
    virtual void HandleEvent(const sf::Event& evt) override final;
    virtual void Update() override final;
};

#endif // TESTSTATE_HPP_
