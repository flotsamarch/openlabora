#ifndef GSMAINMENU_HPP_
#define GSMAINMENU_HPP_

#include "GameState.hpp"

class GSMainMenu final : public GameState
{
public:
    GSMainMenu() = default;
    virtual ~GSMainMenu() override final = default;
    virtual void HandleEvent(const sf::Event& evt) override final;
    virtual void Update() override final;
};

#endif // GSMAINMENU_HPP_
