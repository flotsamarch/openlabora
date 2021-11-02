#ifndef UISMAINMENU_HPP_
#define UISMAINMENU_HPP_

#include "UiState.hpp"

class UISMainMenu final : public UiState
{
public:
    UISMainMenu(State&);
    virtual ~UISMainMenu() override final;
    virtual void HandleEvent(const sf::Event& evt) override final;
    virtual void Update(const float secondsSinceLastUpdate) override final;
};


#endif // UISMAINMENU_HPP_
