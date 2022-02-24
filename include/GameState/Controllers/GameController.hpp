#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <cassert>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "GameState/Controllers/IGameController.hpp"
#include "GameState/Model.hpp"
#include "Game/Playfield.hpp"
#include "Game/IDrawable.hpp"
#include "Game/ISelectable.hpp"
#include "Game/IEntity.hpp"
#include "Game/Location.hpp"

namespace OpenLabora
{

// General game logic base class
class GameController : public IGameController
{
public:
    using Ptr = std::shared_ptr<GameController>;
    using CPtr = std::shared_ptr<const GameController>;

protected:
    const std::weak_ptr<AppStateManager> mState;
    const std::shared_ptr<Model> mModel;

    using SelectableCIterator = Model::CSelectableSpan::iterator;

    // TODO multiplayer support
    std::shared_ptr<Playfield> GetActivePlayerPlayfieldInternal() noexcept
    { return mModel->GetPlayfield(Model::Player1); }

    // Find mutable entity ptr in O(1) by const random access iterator
    // @entity should be contained in mSelectableEntities
    ISelectable::Ptr FindSelectableEntity(SelectableCIterator entity);

public:
    GameController(std::shared_ptr<AppStateManager>,
                   std::shared_ptr<Model>,
                   uint32_t player_count);

    virtual ~GameController() = 0;

    void HandleEvent(const sf::Event&) override;

    void Update(const float update_delta_seconds) override;

    void SetPaused(bool value) noexcept
    { mModel->SetPaused(value); };

    void EnableBuildMode(Location::LocationType);

    std::shared_ptr<const Playfield> GetActivePlayerPlayfield() const noexcept
    { return mModel->GetPlayfield(Model::Player1); }

    const sf::View& GetMainView() const noexcept
    { return mModel->GetMainView(); }

    void MoveMainView(const sf::Vector2f offset)
    { mModel->MoveMainView(offset); }

    void ResetMainView(const sf::FloatRect& viewport)
    { mModel->ResetMainView(viewport); }

    void HandleWindowResize(const sf::Vector2u& window_size) override;

    void IgnoreNextEvent(sf::Event::EventType type)
    { mModel->IgnoreNextEvent(type); }

    void AddPlotToTop(const Plot& plot)
    { GetActivePlayerPlayfieldInternal()->AddPlotToTop(plot); }

    void AddPlotToBottom(const Plot& plot)
    { GetActivePlayerPlayfieldInternal()->AddPlotToBottom(plot); }

    // @entity should be contained in mSelectableEntities
    void SelectEntity(SelectableCIterator entity)
    { FindSelectableEntity(entity)->Select(); }

    // @entity should be contained in mSelectableEntities
    void DeselectEntity(SelectableCIterator entity)
    { FindSelectableEntity(entity)->Deselect(); }

    // @entity should be contained in mSelectableEntities
    void EntityOnHover(SelectableCIterator entity)
    { FindSelectableEntity(entity)->OnHover(); }

    // @entity should be contained in mSelectableEntities
    void EntityOnOut(SelectableCIterator entity)
    { FindSelectableEntity(entity)->OnOut(); }

    template<typename... Args>
    std::shared_ptr<ExpansionMarker> CreateMarker(Args&&... args);

    void RemoveMarker(ExpansionMarker::Ptr marker);
};

inline GameController::~GameController() {}

template<typename... Args>
std::shared_ptr<ExpansionMarker> GameController::CreateMarker(Args&&... args)
{
    return mModel->CreateEntity<ExpansionMarker>(std::forward<Args>(args)...);
}

} // namespace OpenLabora

#endif // GAMESTATE_HPP_
