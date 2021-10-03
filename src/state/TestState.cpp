#include "state/TestState.hpp"

void TestState::HandleEvent(const sf::Event& evt)
{
    if ((evt.type == sf::Event::KeyPressed)
        && (evt.key.code == sf::Keyboard::Escape)) {
        bHasFinished = true;
    }
    return;
}

void TestState::Update()
{
    return;
}
