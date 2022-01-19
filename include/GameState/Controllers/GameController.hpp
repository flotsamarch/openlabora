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
                   unsigned int player_count);

    virtual ~GameController() = 0;

    void HandleEvent(const sf::Event& evt) override;

    void Update(const float update_delta_seconds) override;

    void SetPaused(bool value) noexcept { mModel->bPaused = value; };

    void EnableBuildMode(Location::LocationType);

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

} // namespace OpenLabora

#endif // GAMESTATE_HPP_
