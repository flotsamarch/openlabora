#include "state/gs/GSMainMenu.hpp"

void GSMainMenu::HandleEvent(const sf::Event& evt)
{
    if ((evt.type == sf::Event::KeyPressed)
        && (evt.key.code == sf::Keyboard::Escape)) {
        bIsComplete = true;
    }
    return;
}

void GSMainMenu::Update()
{
    return;
}
