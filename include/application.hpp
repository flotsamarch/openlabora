#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <memory>
#include "IApplication.hpp"
#include "Renderer.hpp"
#include "GameState/Model.hpp"
#include "AppState/Transitions.hpp"
#include "Renderer.hpp"
#include "Misc/PtrView.hpp"
#include "resource/ResourceManager.hpp"

namespace OpenLabora
{

/**
 * Main RAII class for application
 *
 * @tparam TGui - A GUI library class
 * @tparam Window - Render window class
 * @tparam Transitions - Callable for a std::visit that creates new state
 * @tparam TStatesVariant - Variant of all possible states (AppState's)
 * @tparam TStateIdsVariant - Variant of all possible IDs for each state.
 * ID is empty struct that is later used in @Transitions implementation
 */
template <class TGui, class TWindow, class TTransitions,
          class TStatesVariant, class TStateIdsVariant>
class Application final : public IApplication<TStateIdsVariant>
{
    TGui mGui{};
    Renderer<TGui, TWindow> mRenderer{ PtrView(&mGui) };
    Model mModel{ mRenderer.GetWindowSize() };
    IResourceManager::Ptr mResManager = std::make_shared<ResourceManager>();

    TTransitions mTransitions{ PtrView<IApplication<TStateIdsVariant>>(this),
                               mResManager,
                               PtrView(&mGui),
                               PtrView(&mModel) };

    State mState = *std::visit(mTransitions, StateIdsVariant{});

    void HandleEvents();

    template<class TAppState>
    bool IsSameState() { return std::holds_alternative<TAppState>(mState); }
public:
    Application() = default;
    Application(const Application&) = delete;
    Application(Application&&) = delete;
    Application& operator=(const Application&) = delete;
    Application& operator=(Application&&) = delete;

    // Main application loop
    uint32_t run();

    // @arg state_id - Empty struct that represents one of possible app states
    void ChangeState(TStateIdsVariant state_id) override;
};

template <class TGui, class TRenderer, class TTransitions,
          class TStatesVar, class TStateIdsVar>
uint32_t Application<TGui, TRenderer, TTransitions, TStatesVar, TStateIdsVar>
::run()
{
    sf::Clock clock;
    while (mRenderer.IsWindowOpen()) {
        const float delta_seconds = clock.restart().asSeconds();
        HandleEvents();

        auto update = [delta_seconds] (auto&& state) {
            state.view.Update(delta_seconds);
            state.controller->Update(delta_seconds);
        };

        std::visit(update, mState);
        mRenderer.Update(mModel.GetMainView());

        mRenderer.Clear();

        for(auto entity : mModel.GetDrawableEntities()) {
            mRenderer.Draw(entity->GetDrawableObject());
        }
        mRenderer.Display();

        if (IsSameState<FinalState>()) {
            break;
        }
    }
    return 0;
}

template <class TGui, class TRenderer, class TTransitions,
          class TStatesVariant, class TStateIdsVariant>
void Application<TGui, TRenderer, TTransitions, TStatesVariant, TStateIdsVariant>
::ChangeState(TStateIdsVariant state_id)
{
    using OptStates = std::optional<TStatesVariant>;
    OptStates new_state = std::visit(mTransitions, state_id);
    assert(new_state != std::nullopt);
    mGui.removeAllWidgets();
    mState = *std::move(new_state);
}

template <class TGui, class TRenderer, class TTransitions,
          class TStatesVariant, class TStateIdsVariant>
void Application<TGui, TRenderer, TTransitions, TStatesVariant, TStateIdsVariant>
::HandleEvents()
{
    sf::Event evt;
    while (mRenderer.PollEvent(evt)) {
        mRenderer.HandleEvent(evt);
        auto handle = [&evt] (auto&& state) {
            state.view.HandleEvent(evt);
            state.controller->HandleEvent(evt);
        };
        std::visit(handle, mState);
    }
}

} // namespace OpenLabora

#endif // APPLICATION_HPP_
