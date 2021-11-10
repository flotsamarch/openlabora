#ifndef GSMAINMENU_HPP_
#define GSMAINMENU_HPP_

#include "GameState.hpp"

class GSMainMenu final : public GameState
{
public:
    GSMainMenu(State&);
    virtual ~GSMainMenu() override final = default;
    virtual void HandleEvent(const sf::Event& evt) override final;
};

#endif // GSMAINMENU_HPP_
