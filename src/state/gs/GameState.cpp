#include "state/gs/GameState.hpp"
#include "state/State.hpp"

GameState::GameState(std::shared_ptr<State> state) : mState{ state }
{
    auto pos = sf::Mouse::getPosition();
    mMouseX = pos.x;
    mMouseY = pos.y;
}

void GameState::HandleEvent(const sf::Event& evt)
{
    if (evt.type == sf::Event::MouseMoved) {
        mMouseDeltaX = static_cast<float>(evt.mouseMove.x - mMouseX);
        mMouseDeltaY = static_cast<float>(evt.mouseMove.y - mMouseY);
        mMouseX = evt.mouseMove.x;
        mMouseY = evt.mouseMove.y;
    }

    HandleEventImpl(evt);
    return;
}

void GameState::Update([[maybe_unused]]const float secondsSinceLastUpdate)
{
}
