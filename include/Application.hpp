#ifndef APPLICATION_HPP_
#define APPLICATION_HPP_

#include <memory>
#include <variant>
#include "IApplication.hpp"
#include "GameState/Model.hpp"
#include "Renderer.hpp"
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
 * @tparam TTransitions - Callable for a std::visit that creates new state
 * @tparam TStatesVariant - Variant of all possible states (AppState's)
 * @tparam TStateIdsVariant - Variant of all possible IDs for each state.
 * ID is empty struct that is later used in TTransitions implementation
 */
 template<class TGui, class TWindow, template<class...> class TTransitions,
          class TStatesVariant, class TStateIdsVariant, class TResourceManager>
class Application final : public IApplication<TStateIdsVariant>
{
    TGui mGui{};
    TWindow mWindow{};
    Renderer<TGui, TWindow> mRenderer{ PtrView(&mGui), PtrView(&mWindow) };
    IResourceManager::Ptr mResManager = std::make_shared<TResourceManager>();

    using IApplicationPtr = PtrView<IApplication<TStateIdsVariant>>;
    TTransitions<TGui, TWindow> mTransitions
    {
        IApplicationPtr(this), mResManager,
        GameWindow<TGui, TWindow>{PtrView(&mGui), PtrView(&mWindow)}
    };

    TStatesVariant mState = *std::visit(mTransitions, TStateIdsVariant{});

    void HandleEvents();

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

    template<class TAppState>
    bool IsSameState() const noexcept
    { return std::holds_alternative<TAppState>(mState); }

    bool IsFinalState() const noexcept
    { return mState.index() == std::variant_size_v<TStatesVariant> - 1; }
};

 template<class TGui, class TWindow, template<class...> class TTransitions,
          class TStatesVariant, class TStateIdsVariant, class TResourceManager>
uint32_t Application<TGui,
                     TWindow,
                     TTransitions,
                     TStatesVariant,
                     TStateIdsVariant,
                     TResourceManager>
::run()
{
    sf::Clock clock;
    while (mRenderer.IsWindowOpen()) {
        const float delta_seconds = clock.restart().asSeconds();
        HandleEvents();

        auto update = [delta_seconds] (auto&& state) {
            state.view->Update(delta_seconds);
            state.controller->Update(delta_seconds);
        };
        std::visit(update, mState);

        mRenderer.Clear();

        auto get_entities = [] (auto&& state) {
            return state.model->GetDrawableEntities();
        };

        Model::CDrawableSpan entities = std::visit(get_entities, mState);
        for(auto entity : entities) {
            mRenderer.Draw(entity->GetDrawableObject());
        }
        mRenderer.Display();

        if (IsFinalState()) {
            break;
        }
    }
    return 0;
}

 template<class TGui, class TWindow, template<class...> class TTransitions,
          class TStatesVariant, class TStateIdsVariant, class TResourceManager>
void Application<TGui,
                 TWindow,
                 TTransitions,
                 TStatesVariant,
                 TStateIdsVariant,
                 TResourceManager>
::ChangeState(TStateIdsVariant state_id)
{
    using OptStates = std::optional<TStatesVariant>;
    mGui.removeAllWidgets();
    OptStates new_state = std::move(std::visit(mTransitions, state_id));
    assert(new_state != std::nullopt);
    mState = *std::move(new_state);
}

 template<class TGui, class TWindow, template<class...> class TTransitions,
          class TStatesVariant, class TStateIdsVariant, class TResourceManager>
void Application<TGui,
                 TWindow,
                 TTransitions,
                 TStatesVariant,
                 TStateIdsVariant,
                 TResourceManager>
::HandleEvents()
 {
     while (auto&& event = mRenderer.PollEvent()) {
        bool consumed = mRenderer.HandleEvent(*event);
        if (consumed) {
            return;
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
