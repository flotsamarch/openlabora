#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>

class Application;
class UiState;
class GameState;

// Main game application state holder
class State final
{
    std::unique_ptr<GameState> mGameState;
    std::unique_ptr<UiState> mUiState;
    Application& mApp;
public:
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    State(State&&) noexcept;
    State& operator=(State&&) noexcept;

    template <class TStatePair>
    State(TStatePair, Application&, State&);
    template <class TStatePair>
    bool inline IsSameState() const noexcept;

    Application& GetApplication() & noexcept { return mApp; }
    void Update(const float secondsSinceLastCall);
    void HandleEvent(const sf::Event&);
};

// State constructor that uses StateInitializer typedefs
template <class TStatePair>
State::State(TStatePair, Application& app, State& state) : mApp { app }
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    static_assert(std::is_base_of<GameState, gs_t>::value,
                  "CreateState(): GS must inherit from GameState");

    mGameState = std::make_unique<gs_t>(state);
    mUiState = std::make_unique<ui_t>(state);
}

// Compare state to typedef from StateInitializer
template <class TStatePair>
bool State::IsSameState() const noexcept
{
    using gs_t = typename TStatePair::gs_type;
    using ui_t = typename TStatePair::ui_type;

    return dynamic_cast<const gs_t*>(mGameState.get()) != nullptr &&
        dynamic_cast<const ui_t*>(mUiState.get()) != nullptr;
}

#endif // STATE_HPP_
