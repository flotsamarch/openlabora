#ifndef UISFINAL_HPP_
#define UISFINAL_HPP_

#include "UiState.hpp"

class UISFinal final : public UiState
{
public:
    UISFinal(State& state) : UiState{ state } { bIsComplete = true; };
    virtual ~UISFinal() override final = default;
    virtual void HandleEvent([[maybe_unused]] const sf::Event&) override final {};
    virtual void Update([[maybe_unused]]const float) override final {};
};

#endif // UISFINAL_HPP_
