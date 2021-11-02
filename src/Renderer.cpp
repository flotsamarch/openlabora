#include <SFGUI/Container.hpp>
#include <iostream>
#include "Renderer.hpp"
#include "state/gs/GameState.hpp"
#include "state/ui/UiState.hpp"

Renderer::Renderer()
{
    auto video_modes = sf::VideoMode::getFullscreenModes();
    mWindow.create(*video_modes.begin(), // Best video mode is the first
                    std::string(kWindowName),
                    sf::Style::Fullscreen);
    mWindow.setFramerateLimit(kFramerateLimit);
    mWindow.setVerticalSyncEnabled(true);

    // Some SFGUI hack
    // TODO remove once we start using SFML for rendering
    mWindow.resetGLStates();
}

Renderer::~Renderer()
{
    mWindow.close();
}

void Renderer::Render(float secondsSinceLastUpdate)
{
    mDesktop.Update(secondsSinceLastUpdate);
    mWindow.clear();
    mSfgui.Display(mWindow);
    mWindow.display();
}

void Renderer::HandleEvent(const sf::Event& evt)
{
    mDesktop.HandleEvent(evt);
}
