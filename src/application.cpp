#include "Application.hpp"
#include <iostream>
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"

int Application::run()
{
    sf::Clock clock;
    while (mRenderer.IsWindowOpen()) {
        float secondsSinceLastCall = clock.restart().asSeconds();
        HandleEvents();
        mState.Update(secondsSinceLastCall);
        mRenderer.Render(secondsSinceLastCall);
        if (mState.IsSameState<StateInitializers::FinalState>()) {
            break;
        }
    }

    return 0;
}

void Application::HandleEvents()
{
    sf::Event evt;
    while (mRenderer.PollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            mRenderer.RequestCloseWindow();
        }
        mRenderer.HandleEvent(evt);
        mState.HandleEvent(evt);
    }
}
