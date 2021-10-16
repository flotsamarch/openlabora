#ifndef UISMAINMENU_HPP_
#define UISMAINMENU_HPP_

#include "UiState.hpp"

class UISMainMenu final : public UiState
{
public:
    UISMainMenu() = default;
    virtual ~UISMainMenu() override final = default;
    virtual void HandleEvent(const sf::Event& evt) override final;
    virtual void Update() override final;
};


#endif // UISMAINMENU_HPP_