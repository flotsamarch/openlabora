#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <string_view>
#include <SFML/Window.hpp>
#include "state/StateMachine.hpp"

/* RAII class for game application */
class Application
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "OpenLabora" };
    sf::Window mWindow;
    StateMachine mStateMachine;
    void HandleEvents();
public:
    Application();
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;
    int run();
};

#endif // APPLICATION_HPP_
