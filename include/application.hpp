#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <string_view>
#include "state/StateMachine.hpp"
#include "Renderer.hpp"

/* RAII class for game application */
class Application final
{
    Renderer mRenderer;
    StateMachine mStateMachine;
    void HandleEvents();
public:
    Application() = default;
    ~Application() = default;
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;
    int run();
};

#endif // APPLICATION_HPP_
