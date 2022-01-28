#ifndef APPSTATEMANAGER_HPP_
#define APPSTATEMANAGER_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "GameState/Views/IGameView.hpp"
#include "GameState/Controllers/IGameController.hpp"
#include "AppState/AppStateDefs.hpp"
#include "resource/IResourceManager.hpp"

namespace OpenLabora
{

class Model;
class IResourceManager;

// State manager for main application
class AppStateManager final
    : public std::enable_shared_from_this<AppStateManager>
{
    struct ViewControllerPair
    {
        std::shared_ptr<IGameView> gv;
        std::shared_ptr<IGameController> gc;
    };
    ViewControllerPair mState;
    ViewControllerPair mNextState;
    std::shared_ptr<Model> mModel;
    std::unique_ptr<IResourceManager> mResourceManager;

public:
    AppStateManager(std::unique_ptr<IResourceManager> res_mgr,
                    sf::Vector2u window_size);
    ~AppStateManager();

    bool DoesRequireStateChange() const noexcept
    { return mNextState.gv != nullptr && mNextState.gc != nullptr; }

    void ChangeState();

    template <class TStateName>
    void SetNextState();

    template <class TStateName>
    bool inline IsSameState() const noexcept;

    void Update(const float update_delta_seconds);

    void HandleEvent(const sf::Event&);

    IGameController& GetGameController() const noexcept
    { return *mState.gc.get(); }

    IGameView& GetGameView() const noexcept { return *mState.gv.get(); }

    IResourceManager& GetResourceManager() const noexcept
    { return *mResourceManager.get(); }

    const Model& GetModel() const noexcept
    { return *mModel.get(); }
};

// Compare state to typedef from AppStateDef
template <class TStateName>
bool AppStateManager::IsSameState() const noexcept
{
    using view_t = typename TStateName::view_type;
    using ctlr_t = typename TStateName::controller_type;

    // dynamic_cast doesnt throw when used with pointer types
    bool bIsValidGV = dynamic_cast<const view_t*>(mState.gv.get()) != nullptr;
    bool bIsValidGC = dynamic_cast<const ctlr_t*>(mState.gc.get()) != nullptr;
    return bIsValidGC && bIsValidGV;
}

extern template void AppStateManager::SetNextState<AppStateDefs::FinalState>();
extern template void AppStateManager::SetNextState<AppStateDefs::MainMenuState>();
extern template void AppStateManager::SetNextState<AppStateDefs::DuelState>();

} // namespace OpenLabora

#endif // APPSTATEMANAGER_HPP_
