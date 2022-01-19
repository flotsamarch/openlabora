#include <iostream>
#include "SFML/System/Clock.hpp"
#include "Application.hpp"
#include "AppState/AppStateManager.hpp"
#include "AppState/AppStateDefs.hpp"
#include "GameState/Model.hpp"
#include "GameState/Views/GVFinal.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

int Application::run()
{
    sf::Clock clock;
    while (mRenderer->IsWindowOpen()) {
        if (mState->DoesRequireStateChange()) {
            mState->ChangeState();
        }
        float delta_seconds = clock.restart().asSeconds();
        HandleEvents();
        mState->Update(delta_seconds);
        mRenderer->Update(mState->GetModel().mMainView);

        mRenderer->Clear();
        // TODO get and draw objects from model

        // for(auto&& item : game_state.GetDrawableObjectsSpan()) {
        //     if (auto entity = item.lock(); entity != nullptr) {
        //         mRenderer->Draw(entity->GetDrawableObject());
        //     }
        // }
        mRenderer->Display();

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
        mRenderer->HandleEvent(evt);
        mState->HandleEvent(evt);
    }
}

} // namespace OpenLabora
