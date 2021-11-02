#include "state/gs/GSMainMenu.hpp"
#include "state/StateMachine.hpp"
#include "Application.hpp"

GSMainMenu::GSMainMenu(State& state) : GameState{ state }
{
}

void GSMainMenu::HandleEvent(const sf::Event& evt)
{
    if ((evt.type == sf::Event::KeyPressed)
        && (evt.key.code == sf::Keyboard::Escape)) {
        mState.GetApplication().GetStateMachine()
            .ChangeState<StateInitializers::FinalState>();
    }
    return;
}

void GSMainMenu::Update(const float secondsSinceLastUpdate)
{
    return;
}
