#include "Renderer.hpp"

Renderer::Renderer()
{
    auto video_modes = sf::VideoMode::getFullscreenModes();
    mWindow.create(*video_modes.begin(), // Best video mode is the first
                    std::string(kWindowName),
                    sf::Style::Fullscreen);
    mWindow.setFramerateLimit(kFramerateLimit);
    mWindow.setVerticalSyncEnabled(true);
}

Renderer::~Renderer()
{
    mWindow.close();
}
