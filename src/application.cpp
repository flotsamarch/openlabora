#include "Application.hpp"

Application::Application()
{
    auto video_modes = sf::VideoMode::getFullscreenModes();
    mWindow.create(*video_modes.begin(), // Best video mode is the first
                    std::string(kWindowName),
                    sf::Style::Fullscreen);
    mWindow.setFramerateLimit(kFramerateLimit);
    mWindow.setVerticalSyncEnabled(true);
}

int Application::run()
{
    while (mWindow.isOpen()) {
        HandleEvents();
        mStateMachine.UpdateState();
        mStateMachine.AdvanceCompleteState();
        if (mStateMachine.HaveReachedFinalState()) {
            mWindow.close();
        }
    }

    return 0;
}

void Application::HandleEvents()
{
    sf::Event evt;
    while (mWindow.pollEvent(evt)) {
        if (evt.type == sf::Event::Closed) {
            mWindow.close();
        }
        mStateMachine.HandleEvent(evt);
    }
}
