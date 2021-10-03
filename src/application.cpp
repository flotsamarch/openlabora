#include "Application.hpp"
#include "state/TestState.hpp"
#include "state/FinalState.hpp"

Application::Application()
{
    auto video_modes = sf::VideoMode::getFullscreenModes();
    mWindow.create(*video_modes.begin(), // Best video mode is the first
                    std::string(kWindowName),
                    sf::Style::Fullscreen);
    mWindow.setFramerateLimit(kFramerateLimit);
    mWindow.setVerticalSyncEnabled(true);

    mState.SetupState<TestState>();
    mNextState.SetupState<FinalState>();
}

int Application::run()
{
    while (mWindow.isOpen()) {
        HandleEvents();
        mState.Update();
        if (mState.HasFinished()) {
            UpdateStates();
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
        mState.HandleEvent(evt);
    }
}

void Application::UpdateStates()
{
    if (mNextState.HasFinished()) { // Only happens if next state is FinalState
        mWindow.close();
        return;
    }

    mState = std::move(mNextState);
    mNextState.SetupState<FinalState>();
}
