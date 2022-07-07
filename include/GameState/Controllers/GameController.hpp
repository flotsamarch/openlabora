// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <cassert>
#include <memory>
#include <span>
#include <SFML/Window/Event.hpp>
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Model/Model.hpp"
#include "Game/Playfield.hpp"
#include "ECS/Entity.hpp"
#include "Game/MarkerController.hpp"
// TODO: Reimplement Build Mode
// #include "Game/Location.hpp"

namespace OpenLabora
{

// General game logic base class
class GameController : public std::enable_shared_from_this<GameController>
{
    using PlotCreationParams = playfield::PlotCreationParams;

public:
    using Ptr = std::shared_ptr<GameController>;
    using WPtr = std::weak_ptr<GameController>;
    using CPtr = std::shared_ptr<const GameController>;

    using GetPlotCreationParamsDelegate = std::function<PlotCreationParams()>;

protected:
    PtrView<IApplication<StateIdsVariant>> mApp;
    Model::Ptr mModel;
    IResourceManager::Ptr mResourceMgr;

    // TODO: multiplayer support
    Playfield::Ptr GetActivePlayerPlayfieldInternal() noexcept
    { return mModel->GetPlayfield(Model::Player1); }

    Playfield::PtrConst GetActivePlayerPlayfieldInternal() const noexcept
    { return mModel->GetPlayfield(Model::Player1); }

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

    template<model::Drawable T>
    void AddDrawableObject(T&& drawable)
    { mModel->AddDrawableObject(std::forward<T>(drawable)); }

    template<class T>
    uid::Uid AddEntity(T&& entity)
    { return mModel->AddEntity(std::forward<T>(entity)); }

    void RemoveEntity(const uid::Uid& id)
    { mModel->RemoveEntity(id); }

    void RemoveEntityBulk(std::span<uid::Uid> ids)
    { mModel->RemoveEntityBulk(ids); }

    // TODO: Reimplement Build Mode
    // void EnableBuildMode(Location::LocationType);

    const Playfield::PtrConst
    GetActivePlayerPlayfield() const noexcept
    { return GetActivePlayerPlayfieldInternal(); }

    Model::PtrConst GetModel() const
    { return mModel; }

    IResourceManager::Ptr GetResourceManager() const noexcept
    { return mResourceMgr; }

    void SetWorldMousePosition(const sf::Vector2f& position)
    { mModel->SetWorldMousePosition(position); }

    std::function<void()>
    MakePlotCreationDelegate(GetPlotCreationParamsDelegate get_params)
    {
        using playfield::MakePlotCreationDelegate;
        return MakePlotCreationDelegate(GetActivePlayerPlayfieldInternal(),
                                        get_params);
    }
};

inline GameController::~GameController() {}

} // namespace OpenLabora

#endif // GAMESTATE_HPP_
