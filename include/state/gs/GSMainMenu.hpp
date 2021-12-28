#ifndef GSMAINMENU_HPP_
#define GSMAINMENU_HPP_

#include "GameState.hpp"

class GSMainMenu final : public GameState
{
public:
    GSMainMenu(std::shared_ptr<State>);

    void HandleEvent(const sf::Event& evt, IRenderer&) override;
};

#endif // GSMAINMENU_HPP_
