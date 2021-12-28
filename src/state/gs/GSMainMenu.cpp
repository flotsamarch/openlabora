#include "state/gs/GSMainMenu.hpp"

#include <cassert>
#include "state/State.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"

GSMainMenu::GSMainMenu(std::shared_ptr<State> state) : GameState{ state }
{
}

void GSMainMenu::HandleEvent(const sf::Event& evt, IRenderer&)
{
    if ((evt.type == sf::Event::KeyPressed)
        && (evt.key.code == sf::Keyboard::Escape)) {
        assert(!mState.expired());
        mState.lock()->SetNextState<AppStateDefs::FinalState>();
    }
    return;
}
