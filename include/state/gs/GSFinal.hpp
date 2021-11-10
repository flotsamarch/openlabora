#ifndef GSFINAL_HPP_
#define GSFINAL_HPP_

#include "GameState.hpp"

class GSFinal final : public GameState
{
public:
    GSFinal(State& state) : GameState{ state } {};
    virtual ~GSFinal() override final = default;
};

#endif // GSFINAL_HPP_
