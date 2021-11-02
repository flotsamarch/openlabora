#ifndef UISTEST_HPP_
#define UISTEST_HPP_

#include "UiState.hpp"

class UISTest final : public UiState
{
public:
    virtual ~UISTest() override final = default;
    virtual void HandleEvent([[maybe_unused]]const sf::Event&) override final
        { bIsComplete = true; };

    virtual void Update([[maybe_unused]]const float timeSinceLastUpdate)
        override final { bIsComplete = true; };
};


#endif // UISTEST_HPP_
