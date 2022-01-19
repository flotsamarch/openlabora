#include "GameState/Controllers/GCMainMenu.hpp"
#include "AppState/AppStateManager.hpp"

namespace OpenLabora
{

GCMainMenu::GCMainMenu(std::shared_ptr<AppStateManager> state,
                             std::shared_ptr<Model> model)
    : mState{ state }, mModel{ model } {}

GCMainMenu::~GCMainMenu() = default;

void GCMainMenu::HandleEvent(const sf::Event& evt)
{
    if ((evt.type == sf::Event::KeyPressed)
        && (evt.key.code == sf::Keyboard::Escape)) {
        assert(!mState.expired());
        mState.lock()->SetNextState<AppStateDefs::FinalState>();
    }
    return;
}

void GCMainMenu::Update([[maybe_unused]]const float update_delta_seconds) {};

} // namespace OpenLabora
