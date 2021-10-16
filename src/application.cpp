#include "Application.hpp"

int Application::run()
{
    while (mRenderer.IsWindowOpen()) {
        HandleEvents();
        mStateMachine.UpdateState();
        mStateMachine.AdvanceCompleteState();
        if (mStateMachine.HaveReachedFinalState()) {
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
        mStateMachine.HandleEvent(evt);
    }
}
