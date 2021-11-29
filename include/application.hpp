#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <memory>
#include "IApplication.hpp"
#include "state/State.hpp"

/* RAII class for game application */
class Application final : public IApplication
{
protected:
    std::unique_ptr<IRenderer> mRenderer;
    std::shared_ptr<State> mState;
    void HandleEvents();
public:
    template<class TRenderer, class TStatePair>
    Application(TRenderer, TStatePair);

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    int run() override;

    IRenderer* GetRenderer() const noexcept override { return mRenderer.get(); }

    std::shared_ptr<State> GetState() const noexcept override { return mState; }
};

template<class TRenderer, class TStatePair>
Application::Application(TRenderer, TStatePair) :
    mRenderer{ std::make_unique<typename TRenderer::renderer_t>() },
    mState { std::make_shared<State>(*this) }
{
    mState->ChangeState<TStatePair>();
}


#endif // APPLICATION_HPP_
