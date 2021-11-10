#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <string_view>
#include "state/StateMachine.hpp"
#include "state/StateInitializers.hpp"
#include "Renderer.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/ui/UISMainMenu.hpp"

/* RAII class for game application */
class Application final
{
    Renderer mRenderer;
    State mState{ StateInitializers::MainMenuState{}, *this, mState };
    StateMachine mStateMachine{ *this, mState };
    void HandleEvents();
public:
    Application() = default;
    ~Application() = default;
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    int run();
    Renderer& GetRenderer() & { return mRenderer; }
    StateMachine& GetStateMachine() & { return mStateMachine; }
};

#endif // APPLICATION_HPP_
