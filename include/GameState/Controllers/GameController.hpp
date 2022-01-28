#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <cassert>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "GameState/Controllers/IGameController.hpp"
#include "Game/Playfield.hpp"
#include "Game/IDrawable.hpp"
#include "Game/ISelectable.hpp"
#include "Game/IEntity.hpp"
#include "Game/Location.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

template<class TEntity>
concept CEntity = std::derived_from<TEntity, IEntity>;

// General game logic base class
class GameController : public IGameController
{
public:
    using LocationPtr = std::shared_ptr<Location>;

protected:
    const std::weak_ptr<AppStateManager> mState;
    const std::shared_ptr<Model> mModel;

public:
    GameController(std::shared_ptr<AppStateManager>,
                   std::shared_ptr<Model>,
                   size_t player_count);

    virtual ~GameController() = 0;

    void HandleEvent(const sf::Event& evt) override;

    void Update(const float update_delta_seconds) override;

    void SetPaused(bool value) noexcept { mModel->bPaused = value; };

    void EnableBuildMode(Location::LocationType);

    template<CEntity TEntity, class... Args>
    std::shared_ptr<TEntity> CreateEntity(Args&&... args);

    template<CEntity TEntity>
    void RemoveEntity(std::shared_ptr<TEntity> entity);

    // TODO multiplayer support
    std::shared_ptr<Playfield> GetActivePlayerPlayfield() const noexcept
    { return mModel->mPlayfields[Model::Player1]; }

    void SetBuildGhostPosition(const sf::Vector2f& position)
    { mModel->mBuildGhost->SetPosition(position); }

    void SetBuildGhostPosition(float position_x, float position_y)
    { mModel->mBuildGhost->SetPosition(position_x, position_y); }

    sf::View& GetMainView() & noexcept { return mModel->mMainView; }

    void HandleWindowResize(const sf::Vector2u& window_size);
};

inline GameController::~GameController() {}

template<CEntity TEntity, class... Args>
std::shared_ptr<TEntity> GameController::CreateEntity(Args&&... args)
{
    auto entity = std::make_shared<TEntity>(std::forward<Args>(args)...);
    mModel->mEntities.push_back(entity);

    if constexpr(std::derived_from<TEntity, IDrawable>) {
        auto drwbl_entity = std::static_pointer_cast<IDrawable>(entity);
        mModel->mDrawableEntities.push_back(drwbl_entity);
    }

    if constexpr(std::derived_from<TEntity, ISelectable>) {
        auto sel_entity = std::static_pointer_cast<ISelectable>(entity);
        mModel->mSelectableEntities.push_back(sel_entity);
    }

    return entity;
}

template<CEntity TEntity>
void GameController::RemoveEntity(std::shared_ptr<TEntity> entity)
{
    {
        auto to_remove = std::ranges::find(mModel->mEntities, entity);
        mModel->mEntities.erase(to_remove);
    }

    if constexpr(std::derived_from<TEntity, IDrawable>) {
        auto sel_entity = std::static_pointer_cast<IDrawable>(entity);
        auto to_remove = std::ranges::find(mModel->mDrawableEntities, entity);
        mModel->mDrawableEntities.erase(to_remove);
    }

    if constexpr(std::derived_from<TEntity, ISelectable>) {
        auto sel_entity = std::static_pointer_cast<ISelectable>(entity);
        auto to_remove = std::ranges::find(mModel->mSelectableEntities, entity);
        mModel->mSelectableEntities.erase(to_remove);
    }
}

} // namespace OpenLabora

#endif // GAMESTATE_HPP_
