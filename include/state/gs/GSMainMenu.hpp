#ifndef GSMAINMENU_HPP_
#define GSMAINMENU_HPP_

#include "GameState.hpp"

class GSMainMenu final : public GameState
{
public:
    GSMainMenu(std::shared_ptr<State>);

    void HandleEventImpl(const sf::Event& evt) override;
};

#endif // GSMAINMENU_HPP_
