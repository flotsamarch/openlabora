#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "state/gs/IGameState.hpp"
#include "game/GameObject.hpp"

class State;

// General game logic base class
class GameState : public IGameState
{
protected:
    std::vector<GameObject::UPtr> mGameObjects;
    std::weak_ptr<State> mState;

    int mMouseX = 0, mMouseY = 0;
    float mMouseDeltaX = 0, mMouseDeltaY = 0;
public:
    GameState(std::shared_ptr<State> state) : mState{ state }
        {
            auto pos = sf::Mouse::getPosition();
            mMouseX = pos.x;
            mMouseY = pos.y;
        };

    virtual inline ~GameState() noexcept = 0;

    void HandleEvent(const sf::Event& evt) override final
        {
            if (evt.type == sf::Event::MouseMoved) {
                mMouseDeltaX = static_cast<float>(evt.mouseMove.x - mMouseX);
                mMouseDeltaY = static_cast<float>(evt.mouseMove.y - mMouseY);
                mMouseX = evt.mouseMove.x;
                mMouseY = evt.mouseMove.y;
            }
            HandleEventImpl(evt);
        };

    void HandleEventImpl(const sf::Event&) override {};

    void Update([[maybe_unused]]const float seconds) override {};

    GameObject::Iter GetGameObjectBegin() noexcept override
        { return mGameObjects.begin(); }

    GameObject::Iter GetGameObjectEnd() noexcept override
        { return mGameObjects.end(); }
};

inline GameState::~GameState() noexcept {};

#endif // GAMESTATE_HPP_
