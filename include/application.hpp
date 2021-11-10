#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <string_view>
#include "state/StateMachine.hpp"
#include "state/StateInitializers.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/ui/UISMainMenu.hpp"

class Renderer;

/* RAII class for game application */
class Application
{
    std::unique_ptr<Renderer> mRenderer;
    State mState{ StateInitializers::MainMenuState{}, *this, mState };
    StateMachine mStateMachine{ *this, mState };
    void HandleEvents();
public:
    Application();
    ~Application();
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    int run();
    Renderer* GetRenderer() const noexcept { return mRenderer.get(); }
    StateMachine& GetStateMachine() & { return mStateMachine; }
};

#endif // APPLICATION_HPP_
