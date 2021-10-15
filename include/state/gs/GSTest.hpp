#ifndef GSTEST_HPP_
#define GSTEST_HPP_

#include "GameState.hpp"

class GSTest final : public GameState
{
public:
    virtual ~GSTest() override final = default;
    virtual void HandleEvent([[maybe_unused]]const sf::Event& evt) override final
    { bIsComplete = true; };

    virtual void Update() override final { bIsComplete = true; };
};

#endif // GSTEST_HPP_
