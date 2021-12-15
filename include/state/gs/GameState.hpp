#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <cassert>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "state/gs/IGameState.hpp"
#include "game/GameObject.hpp"
#include "game/Playfield.hpp"
#include "game/IDrawable.hpp"

class State;

// General game logic base class
class GameState : public IGameState
{
protected:
    std::vector<IDrawable::Ptr> mGameObjects;
    std::weak_ptr<State> mState;
    std::shared_ptr<Playfield> mPlayfield;
    std::shared_ptr<Location> mBuildGhost;
    bool bBuildModeEnabled{ false };
    bool bPaused{ false };

    int mMouseX = 0, mMouseY = 0;
    float mMouseDeltaX = 0, mMouseDeltaY = 0;
public:
    GameState(std::shared_ptr<State>);

    virtual inline ~GameState() noexcept = 0;

    void HandleEvent(const sf::Event& evt) override final;

    void HandleEventImpl(const sf::Event&) override {};

    void Update(const float secondsSinceLastUpdate) override;

    void SetPaused(bool paused) noexcept override { bPaused = paused; }

    bool IsPaused() noexcept override { return bPaused; }

    IDrawable::Iter GetGameObjectBegin() noexcept override
        { return mGameObjects.begin(); }

    IDrawable::Iter GetGameObjectEnd() noexcept override
        { return mGameObjects.end(); }
};

inline GameState::~GameState() noexcept {};

#endif // GAMESTATE_HPP_
