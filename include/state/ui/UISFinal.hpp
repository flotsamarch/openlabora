#ifndef UISFINAL_HPP_
#define UISFINAL_HPP_

#include "UiState.hpp"

class UISFinal final : public UiState
{
public:
    UISFinal() { bIsComplete = true; };
    virtual ~UISFinal() override final = default;
    virtual void HandleEvent([[maybe_unused]] const sf::Event& evt) override final {};
    virtual void Update() override final {};
};

#endif // UISFINAL_HPP_
