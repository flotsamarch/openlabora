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
#include "IApplication.hpp"
#include "GameState/Model/Model.hpp"
#include "Misc/PtrView.hpp"
#include "GameWindow.hpp"
#include "Resource/IResourceManager.hpp"

namespace OpenLabora
{

/**
 * Main RAII class for application
 *
 * @tparam TGui - A GUI library class
 * @tparam TWindow - Render window class
 * @tparam TRenderer - Wrapper for graphics and GUI libraries
 * @tparam TTransitions - Callable for a std::visit that creates new state
 * @tparam TStatesVariant - Variant of all possible states (AppState's)
 * @tparam TStateIdsVariant - Variant of all possible IDs for each state.
 * ID is empty struct that is later used in TTransitions implementation
 */
template<class TGui, class TWindow, template<class...> class TRenderer,
         template<class...> class TTransitions, class TStatesVariant,
         class TStateIdsVariant, class TResourceManager>
class Application final : public IApplication<TStateIdsVariant>
{
    using Clock = std::chrono::steady_clock;
    TGui mGui{};
    TWindow mWindow{};
    TRenderer<TGui, TWindow> mRenderer{ PtrView(&mGui), PtrView(&mWindow) };
    IResourceManager::Ptr mResourceMgr = std::make_shared<TResourceManager>();

    using IApplicationPtr = PtrView<IApplication<TStateIdsVariant>>;
    TTransitions<TGui, TWindow> mTransitions
    {
        IApplicationPtr(this), mResourceMgr,
        GameWindow<TGui, TWindow>{PtrView(&mGui), PtrView(&mWindow)}
    };

    TStatesVariant mState = *std::visit(mTransitions, TStateIdsVariant{});

public:
    Application(const std::filesystem::path& path) :
        mResourceMgr{ std::make_shared<TResourceManager>(path) } {}

    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    // Main application loop
    uint32_t run();

    // @arg state_id - Empty struct that represents one of possible app states
    void ChangeState(TStateIdsVariant state_id) override;

    template<class TAppState>
    bool IsSameState() const noexcept
    { return std::holds_alternative<TAppState>(mState); }

    bool IsFinalState() const noexcept
    { return mState.index() == std::variant_size_v<TStatesVariant> - 1; }

    IResourceManager::Ptr GetResourceMgr() const { return mResourceMgr; }
    TStatesVariant& GetState() noexcept { return mState; }
    TRenderer<TGui, TWindow>& GetRenderer() noexcept
    { return mRenderer; }

    void HandleEvents();
};

template<class TGui, class TWindow, template<class...> class TRenderer,
         template<class...> class TTransitions, class TStatesVariant,
         class TStateIdsVariant, class TResourceManager>
uint32_t Application<TGui,
                     TWindow,
                     TRenderer,
                     TTransitions,
                     TStatesVariant,
                     TStateIdsVariant,
                     TResourceManager>
::run()
{
    auto start_time = Clock::now();
    while (mRenderer.IsWindowOpen()) {
        auto end_time = Clock::now();
        std::chrono::duration<float> delta_seconds = end_time - start_time;
        start_time = end_time;

        HandleEvents();

        auto update = [ds = delta_seconds.count()] (auto&& state) {
            state.view->Update(ds);
            state.controller->Update(ds);
        };
        std::visit(update, mState);

        mRenderer.Clear();

        auto get_drawable_objects = [] (auto&& state) {
            return state.model->GetDrawableObjects();
        };

        auto&& drawable_objects = std::visit(get_drawable_objects, mState);
        for(auto&& drawable : drawable_objects) {
            mRenderer.Draw(*drawable);
        }
        mRenderer.Display();

        if (IsFinalState()) {
            break;
        }
    }
    return 0;
}

template<class TGui, class TWindow, template<class...> class TRenderer,
         template<class...> class TTransitions, class TStatesVariant,
         class TStateIdsVariant, class TResourceManager>
void Application<TGui,
                 TWindow,
                 TRenderer,
                 TTransitions,
                 TStatesVariant,
                 TStateIdsVariant,
                 TResourceManager>
::ChangeState(TStateIdsVariant state_id)
{
    using OptStates = std::optional<TStatesVariant>;
    mRenderer.RemoveAllWidgets();
    OptStates new_state = std::move(std::visit(mTransitions, state_id));
    mState = *std::move(new_state);
}

template<class TGui, class TWindow, template<class...> class TRenderer,
         template<class...> class TTransitions, class TStatesVariant,
         class TStateIdsVariant, class TResourceManager>
void Application<TGui,
                 TWindow,
                 TRenderer,
                 TTransitions,
                 TStatesVariant,
                 TStateIdsVariant,
                 TResourceManager>
::HandleEvents()
 {
     while (auto&& event = mRenderer.PollEvent()) {
        bool consumed = mRenderer.HandleEvent(*event);
        if (consumed) {
            continue;
        }
        auto handle = [&evt = *event] (auto&& state) {
            state.view->HandleEvent(evt);
            state.controller->HandleEvent(evt);
        };
        std::visit(handle, mState);
    }
}

} // namespace OpenLabora

#endif // APPLICATION_HPP_
