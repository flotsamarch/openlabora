#ifndef GSFINAL_HPP_
#define GSFINAL_HPP_

#include "GameState.hpp"

class GSFinal final : public GameState
{
public:
    GSFinal(State& state) : GameState{ state } { bIsComplete = true; };
    virtual ~GSFinal() override final = default;
    virtual void HandleEvent([[maybe_unused]] const sf::Event&) override final {};
    virtual void Update([[maybe_unused]]const float) override final {};
};

#endif // GSFINAL_HPP_
