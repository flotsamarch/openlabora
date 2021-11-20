#ifndef GSFINAL_HPP_
#define GSFINAL_HPP_

#include "GameState.hpp"

class GSFinal final : public GameState
{
public:
    GSFinal(std::shared_ptr<State> state) : GameState{ state } {};
};

#endif // GSFINAL_HPP_
