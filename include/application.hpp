#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <memory>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Button.hpp>
#include <SFGUI/Box.hpp>
#include "IApplication.hpp"
#include "resource/ResourceManager.hpp"
#include "IRenderer.hpp"
#include "AppState/AppStateManager.hpp"

namespace OpenLabora
{

class Application final : public IApplication
{
protected:
    std::unique_ptr<IRenderer> mRenderer;
    std::shared_ptr<AppStateManager> mState;
    void HandleEvents();
public:
    template<class TStateName>
    Application(TStateName, std::unique_ptr<IRenderer>);

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    int run() override;
};

template<class TStateName>
Application::Application(TStateName,
                         std::unique_ptr<IRenderer> renderer)
    : mRenderer{ std::move(renderer) }
{
    auto res_mgr = std::make_unique<ResourceManager>();
    mState = std::make_shared<AppStateManager>(std::move(res_mgr),
                                               mRenderer->GetWindowSize());
    mState->SetNextState<TStateName>();
}

} // namespace OpenLabora

#endif // APPLICATION_HPP_
