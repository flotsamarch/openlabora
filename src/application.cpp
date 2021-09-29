#include "application.hpp"

Application::Application()
{
    auto video_modes = sf::VideoMode::getFullscreenModes();
    m_window.create(*video_modes.begin(), // Best video mode is the first
                    std::string(windowName),
                    sf::Style::Fullscreen);
    m_window.setFramerateLimit(framerateLimit);
    m_window.setVerticalSyncEnabled(true);
}

int Application::run()
{
    while (m_window.isOpen()) {
        sf::Event event;
        while (m_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_window.close();
            }
            if ((event.type == sf::Event::KeyPressed)
                && (event.key.code == sf::Keyboard::Escape)) {
                m_window.close();
            }
        }
    }

    return 0;
}
