#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <cassert>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "state/gs/IGameState.hpp"
#include "game/Playfield.hpp"
#include "game/IDrawable.hpp"
#include "game/ISelectable.hpp"
#include "game/Entity.hpp"
#include "game/Location.hpp"

class State;

// General game logic base class
class GameState : public IGameState
{
public:
    using LocationPtr = std::shared_ptr<Location>;
protected:
    using LocationSubArray = std::array<LocationPtr, Playfield::kFieldWidth>;
    using LocationArray = std::array<LocationSubArray, Playfield::kFieldHeight>;
    // using LocationIter = LocationSubArray::const_iterator;
    std::vector<std::shared_ptr<Entity>> mEntities;
    std::vector<std::weak_ptr<IDrawable>> mDrawableObjects;
    std::vector<std::weak_ptr<ISelectable>> mSelectableObjects;
    std::weak_ptr<State> mState;

    template <class TEntity, class... Args>
    std::shared_ptr<TEntity> CreateEntity(Args&&... args)
    {
        auto entity = std::make_shared<TEntity>(std::forward<Args>(args)...);
        mEntities.push_back(entity);
        mDrawableObjects.push_back(entity);

        if constexpr (std::derived_from<TEntity, ISelectable>) {
            mSelectableObjects.emplace_back(entity);
        }
        return entity;
    }
public:
    GameState(std::shared_ptr<State>);

    virtual inline ~GameState() noexcept = 0;

    void HandleEvent([[maybe_unused]]const sf::Event& evt,
                     [[maybe_unused]]IRenderer&) override {};

    void Update([[maybe_unused]]const float secondsSinceLastUpdate,
                 IRenderer&) override {};

    IGameState::DrawableSpan GetDrawableObjectsSpan() noexcept override
        { return {mDrawableObjects.begin(), mDrawableObjects.end()}; }
};

inline GameState::~GameState() noexcept {};

#endif // GAMESTATE_HPP_
