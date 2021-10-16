#ifndef UISTEST_HPP_
#define UISTEST_HPP_

#include "UiState.hpp"

class UISTest final : public UiState
{
public:
    virtual ~UISTest() override final = default;
    virtual void HandleEvent([[maybe_unused]]const sf::Event& evt) override final
    { bIsComplete = true; };

    virtual void Update() override final { bIsComplete = true; };
};


#endif // UISTEST_HPP_
