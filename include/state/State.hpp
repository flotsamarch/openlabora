#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "state/gs/IGameState.hpp"
#include "state/ui/IUiState.hpp"
#include "IApplication.hpp"
#include "AppStateDefs.hpp"

class Application;

class UiState;
class GameState;

// Main game application state holder
class State final : public std::enable_shared_from_this<State>
{
    struct StatePair
    {
        std::unique_ptr<IGameState> gs;
        std::unique_ptr<IUiState> uis;
    };
    StatePair mState;
    StatePair mNextState;
    std::unique_ptr<IResourceManager> mResourceManager;
    const sf::VideoMode& mVideoMode;

public:
    State(std::unique_ptr<IResourceManager> res_mgr, const sf::VideoMode& vm) :
        mResourceManager{ std::move(res_mgr) },
        mVideoMode{ vm } {};

    bool DoesRequireStateChange() const noexcept
    {
        return mNextState.gs != nullptr && mNextState.uis != nullptr;
    }

    void ChangeState();

    template <class TStatePair>
    void SetNextState();

    template <class TStatePair>
    bool inline IsSameState() const noexcept;

    void Update(const float secondsSinceLastCall, IRenderer&);

    void HandleEvent(const sf::Event&, IRenderer&);

    IGameState& GetGameState() const noexcept
        { return *mState.gs.get(); }

    IUiState& GetUiState() const noexcept { return *mState.uis.get(); }

    IResourceManager& GetResourceManager() const noexcept
        { return *mResourceManager.get(); }
};

// Compare state to typedef from AppStateDef
template <class TStatePair>
bool State::IsSameState() const noexcept
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    // dynamic_cast doesnt throw when used with pointer types
    bool bIsValidGS = dynamic_cast<const gs_t*>(mState.gs.get()) != nullptr;
    bool bIsValidUIS = dynamic_cast<const ui_t*>(mState.uis.get()) != nullptr;
    return bIsValidGS && bIsValidUIS;
}

extern template void State::SetNextState<AppStateDefs::FinalState>();
extern template void State::SetNextState<AppStateDefs::MainMenuState>();
extern template void State::SetNextState<AppStateDefs::DuelState>();

#endif // STATE_HPP_
