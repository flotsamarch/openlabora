// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <memory>
#include <variant>
#include <chrono>
#include <filesystem>
#include "ApplicationState/ApplicationContext.hpp"
#include "Misc/PtrView.hpp"
#include "IGameWindow.hpp"
#include "Resource/IResourceManager.hpp"
#include "Input/Input.hpp"

namespace open_labora
{

/**
 * Main RAII class for application
 *
 * @tparam TGui - A GUI library class
 * @tparam TWindow - Render window class
 * @tparam TRenderer - Wrapper for graphics and GUI libraries
 * @tparam TResourceManager - Resource manager class
 */
template<class TGui,
         class TWindow,
         class TGameWindow,
         template<class...> class TRenderer,
         class TResourceManager>
class Application final : public ApplicationContext
{
    using Clock = std::chrono::steady_clock;
    TGui mGui{};
    TWindow mWindow{};
    TRenderer<TGui, TWindow> mRenderer{ PtrView(&mGui), PtrView(&mWindow) };
    IResourceManager::Ptr mResourceMgr = std::make_shared<TResourceManager>();
    Input mInput{};

    void HandleEvents();

public:
    Application(const std::filesystem::path& path)
        : mResourceMgr{ std::make_shared<TResourceManager>(path) } {}

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    // Main application loop
    uint32_t run();

    IResourceManager::Ptr GetResourceMgr() const
    { return mResourceMgr; }

    TRenderer<TGui, TWindow>& GetRenderer() noexcept
    { return mRenderer; }

    IGameWindow::Ptr GetGameWindow()
    {
        return std::make_shared<TGameWindow>(PtrView{ &mGui },
                                             PtrView{ &mWindow });
    }

    bool HasReachedFinalState()
    { return stateGetFlagIsFinal(mState); }

    const ApplicationState& GetState() const noexcept
    { return mState; }

    Input& GetInput() noexcept
    { return mInput; }
};

template<class TGui,
         class TWindow,
         class TGameWindow,
         template<class...> class TRenderer,
         class TResourceManager>
uint32_t Application<TGui, TWindow, TGameWindow, TRenderer, TResourceManager>
::run()
{
    auto start_time = Clock::now();
    while (mRenderer.IsWindowOpen()) {
        auto end_time = Clock::now();
        std::chrono::duration<float> delta_seconds = end_time - start_time;
        start_time = end_time;

        mInput.Update(delta_seconds.count());

        HandleEvents();

        stateUpdate(mState, delta_seconds.count());

        mRenderer.Clear();

        auto&& drawable_range = stateGetDrawableObjects(mState);
        mRenderer.Draw(drawable_range);
        mRenderer.Display();

        if (HasReachedFinalState()) {
            break;
        }
    }
    return 0;
}

template<class TGui,
         class TWindow,
         class TGameWindow,
         template<class...> class TRenderer,
         class TResourceManager>
void Application<TGui, TWindow, TGameWindow, TRenderer, TResourceManager>
::HandleEvents()
{
     while (auto&& event = mRenderer.PollEvent()) {
         bool consumed = mRenderer.HandleEvent(*event);
         if (consumed) {
             continue;
         }

         mInput.HandleEvent(*event);
         while (mInput.HasUnhandledInput()) {
             stateHandleInput(mState, Input::PtrConst{ &mInput });
             mInput.Advance();
         }
    }
}

} // namespace open_labora

#endif // APPLICATION_HPP_
