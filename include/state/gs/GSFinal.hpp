#ifndef GSFINAL_HPP_
#define GSFINAL_HPP_

#include "GameState.hpp"

class GSFinal final : public GameState
{
public:
    GSFinal() { bIsComplete = true; };
    virtual ~GSFinal() override final = default;
    virtual void HandleEvent([[maybe_unused]] const sf::Event& evt) override final {};
    virtual void Update() override final {};
};

#endif // GSFINAL_HPP_
