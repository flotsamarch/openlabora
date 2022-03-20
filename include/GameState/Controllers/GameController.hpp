#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <cassert>
#include <memory>
#include <SFML/Window/Event.hpp>
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Model.hpp"
#include "Game/Playfield.hpp"
#include "Game/IDrawable.hpp"
#include "Game/Selectable.hpp"
#include "Game/IEntity.hpp"
#include "Game/Location.hpp"

namespace OpenLabora
{

// General game logic base class
class GameController
{
public:
    using Ptr = std::shared_ptr<GameController>;
    using WPtr = std::weak_ptr<GameController>;
    using CPtr = std::shared_ptr<const GameController>;

protected:
    PtrView<IApplication<StateIdsVariant>> mApp;
    Model::Ptr mModel;
    IResourceManager::Ptr mResManager;

    using SelectableCIterator = Model::CSelectableSpan::iterator;

    // TODO multiplayer support
    std::shared_ptr<Playfield> GetActivePlayerPlayfieldInternal() noexcept
    { return mModel->GetPlayfield(Model::Player1); }
    // Find mutable entity ptr in O(1) by const random access iterator
    // @arg entity - should be contained in mSelectableEntities
    Selectable::Ptr FindSelectableEntity(SelectableCIterator entity);

public:
    GameController(PtrView<IApplication<StateIdsVariant>>,
                   IResourceManager::Ptr,
                   Model::Ptr,
                   uint32_t player_count);

    virtual ~GameController() = 0;

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);

    void SetPaused(bool value) noexcept
    { mModel->SetPaused(value); };

    void EnableBuildMode(Location::LocationType);

    std::shared_ptr<const Playfield> GetActivePlayerPlayfield() const noexcept
    { return mModel->GetPlayfield(Model::Player1); }

    void HandleWindowResize(const sf::Vector2u& window_size);

    void AddPlotToTop(const Plot& plot)
    { GetActivePlayerPlayfieldInternal()->AddPlotToTop(plot); }

    void AddPlotToBottom(const Plot& plot)
    { GetActivePlayerPlayfieldInternal()->AddPlotToBottom(plot); }

    template<typename... Args>
    std::shared_ptr<ExpansionMarker> CreateMarker(Args&&... args);

    void RemoveMarker(ExpansionMarker::Ptr marker);

    IResourceManager::Ptr GetResourceManager() const noexcept
    { return mResManager; }
};

inline GameController::~GameController() {}

template<typename... Args>
std::shared_ptr<ExpansionMarker> GameController::CreateMarker(Args&&... args)
{
    return mModel->CreateEntity<ExpansionMarker>(std::forward<Args>(args)...);
}

} // namespace OpenLabora

#endif // GAMESTATE_HPP_
