#include <iostream>
#include "SFML/System/Clock.hpp"
#include "Application.hpp"
#include "state/State.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"
#include "state/AppStateDefs.hpp"

int Application::run()
{
    sf::Clock clock;
    while (mRenderer->IsWindowOpen()) {
        if (mState->DoesRequireStateChange()) {
            mState->ChangeState();
        }
        float secondsSinceLastCall = clock.restart().asSeconds();
        HandleEvents();
        mState->Update(secondsSinceLastCall, *mRenderer.get());
        auto&& game_state = mState->GetGameState();

        mRenderer->Clear();
        for(auto&& item : game_state.GetDrawableObjectsSpan()) {
            if (auto entity = item.lock(); entity != nullptr) {
                mRenderer->Draw(entity->GetDrawableObject());
            }
        }
        mRenderer->Update(secondsSinceLastCall);

        if (mState->IsSameState<AppStateDefs::FinalState>()) {
            break;
        }
    }

    return 0;
}

void Application::HandleEvents()
{
    sf::Event evt;
    while (mRenderer->PollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            mRenderer->RequestCloseWindow();
        }
        mState->HandleEvent(evt, *mRenderer.get());
    }
}
