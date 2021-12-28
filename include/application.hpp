#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <memory>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "IApplication.hpp"
#include "resource/ResourceManager.hpp"
#include "IRenderer.hpp"
#include "state/State.hpp"

/* RAII class for game application */
class Application final : public IApplication
{
protected:
    std::unique_ptr<IRenderer> mRenderer;
    std::shared_ptr<State> mState;
    void HandleEvents();
public:
    template<class TStatePair>
    Application(TStatePair, std::unique_ptr<IRenderer>);

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    int run() override;
};

template<class TStatePair>
Application::Application(TStatePair,
            std::unique_ptr<IRenderer> renderer) :
    mRenderer{ std::move(renderer) },
    mState { std::make_shared<State>(std::make_unique<ResourceManager>(),
                                     mRenderer->GetVideoMode()) }
{
    mState->SetNextState<TStatePair>();
}


#endif // APPLICATION_HPP_
