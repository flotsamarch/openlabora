#ifndef STATE_HPP_
#define STATE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>

class GameState;
class FinalState;
class TestState;

class State
{
    std::unique_ptr<GameState> mGameState;
public:
    State();
    ~State();
    State(State&&);
    State& operator=(State&&);
    State(const State&) = delete;
    State& operator=(const State&) = delete;

    template <class GS>
    void SetupState();
    void Update();
    void HandleEvent(const sf::Event& evt);
    bool HasFinished() const;
};

extern template void State::SetupState<FinalState>();
extern template void State::SetupState<TestState>();

#endif // STATE_HPP_
