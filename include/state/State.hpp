#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "state/gs/IGameState.hpp"
#include "state/ui/IUiState.hpp"
#include "IApplication.hpp"

class Application;

class UiState;
class GameState;

// Main game application state holder
class State final : public std::enable_shared_from_this<State>
{
    std::unique_ptr<IGameState> mGameState;
    std::unique_ptr<IUiState> mUiState;
    IApplication& mApp;
public:
    State(IApplication& app) : mApp { app } {};

    template <class TStatePair>
    void ChangeState();

    template <class TStatePair>
    bool inline IsSameState() const noexcept;

    IApplication& GetApp() const noexcept { return mApp; }

    void Update(const float secondsSinceLastCall);

    void HandleEvent(const sf::Event&);

    IGameState& GetGameState() const noexcept { return *mGameState.get(); }

    IUiState& GetUiState() const noexcept { return *mUiState.get(); }
};


template <class TStatePair>
void State::ChangeState()
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    static_assert(std::is_base_of<IGameState, gs_t>::value,
                  "CreateState(): GS must inherit from GameState");
    static_assert(std::is_base_of<IUiState, ui_t>::value,
                  "CreateState(): GS must inherit from GameState");

    mGameState.reset();
    mGameState = std::make_unique<gs_t>(shared_from_this());
    mUiState.reset();
    mUiState = std::make_unique<ui_t>(shared_from_this());
}

// Compare state to typedef from AppStateDef
template <class TStatePair>
bool State::IsSameState() const noexcept
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    // dynamic_cast doesnt throw when used with pointer types
    bool bIsValidGS = dynamic_cast<const gs_t*>(mGameState.get()) != nullptr;
    bool bIsValidUIS = dynamic_cast<const ui_t*>(mUiState.get()) != nullptr;
    return bIsValidGS && bIsValidUIS;
}

#endif // STATE_HPP_
