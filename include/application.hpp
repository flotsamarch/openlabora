#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <string_view>
#include <SFML/Window.hpp>

/* RAII class for game application */
class Application
{
    static constexpr int framerateLimit{ 144 };
    static constexpr std::string_view windowName{ "OpenLabora" };
    sf::Window m_window;
public:
    Application();
    int run();
};

#endif // APPLICATION_HPP_
