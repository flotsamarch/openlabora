#include "state/gs/GSMainMenu.hpp"
#include "Application.hpp"
#include "state/StateMachine.hpp"
#include "state/StateInitializers.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"

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
