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

#include <tuple>
#include "LibTypedefs.hpp"
#include "Misc/TupleUtils.hpp"
#include "GameState/ViewToViewModelBinding.hpp"
#include "ApplicationState/ApplicationContext.hpp"
#include "Resource/IResourceManager.hpp"
#include "IGameWindow.hpp"
#include "Input/Input.hpp"

namespace open_labora
{

/**
 * Gameplay state that implements MVVM pattern
 *
 * @tparam TGameController - game logic controller class
 * @tparam TModel - model component of mvvm
 * @tparam TViewToViewModelBindings - list of View-ViewModel pairs wrapped in
 *     ViewToViewModelBinding class
 */
template<template<class...> class TGameController,
         class TModel,
         class... TViewToViewModelBindings>
class GameState final
{
public:
    using VVMBindings = std::tuple<TViewToViewModelBindings...>;
    using ModelPtr = std::unique_ptr<TModel>;

private:
    ApplicationContext::Ptr mApp;
    IResourceManager::Ptr mResourceMgr;
    IGameWindow::Ptr mWindow;
    ModelPtr mModel;
    TGameController<TModel> mGameController;
    VVMBindings mVVMBindings;

    // Create a tuple of special initializer objects for VVMBindings
    static auto createInitializer(ApplicationContext::Ptr app,
                                  IGameWindow::Ptr window,
                                  PtrView<TModel> model)
    {
        using tuple_utils::createTuple;
        constexpr auto size = sizeof...(TViewToViewModelBindings);
        using BI = BindingInitializer<TModel>;
        return createTuple<BI, size>({ app, window, model });
    }

public:
    ~GameState()
    { mWindow->RemoveAllWidgets(); }

    GameState(const GameState&) = delete;
    GameState(GameState&&) = delete;
    GameState& operator=(const GameState&) = delete;
    GameState& operator=(GameState&&) = delete;

    GameState(ApplicationContext::Ptr app,
              IGameWindow::Ptr window,
              IResourceManager::Ptr resource_mgr,
              ModelPtr model,
              std::function<void(VVMBindings&)> setup_intermodule)
        : mApp{ app },
          mWindow{ window },
          mResourceMgr{ resource_mgr },
          mModel{ std::move(model) },
          mGameController{ app, resource_mgr, PtrView{ mModel.get() }, 2 },
          mVVMBindings{ createInitializer(app, window, PtrView{ mModel.get() }) }
    {
        setup_intermodule(mVVMBindings);
    }

    void HandleInput(Input::PtrConst);

    void Update(float update_delta_seconds);

    void MapScreenCoordsToWorld(const Vector2i& point)
    { mModel->SetWorldMousePosition(mWindow->MapScreenToWorldCoords(point)); }

    TModel& GetModel() noexcept
    { return *mModel; }

    IGameWindow::Ptr GetWindow()
    { return mWindow; }

    IResourceManager::Ptr GetResourceManager()
    { return mResourceMgr; }
};

template<template<class...> class TGameController,
         class TModel,
         class... TViewToViewModelBindings>
void GameState<TGameController, TModel, TViewToViewModelBindings...>
::HandleInput(Input::PtrConst input)
{
    bool propagate = true;
    auto pred = [&propagate] (auto&&) { return propagate; };
    auto handle_events = [&propagate, input] (auto&& binding)
    {
        propagate = !binding.view.HandleInput(input);
    };

    tuple_utils::applyUntilFalse(mVVMBindings, handle_events, pred);
}

template<template<class...> class TGameController,
         class TModel,
         class... TViewToViewModelBindings>
void GameState<TGameController, TModel, TViewToViewModelBindings...>
::Update(float update_delta_seconds)
{
    mModel->ClearDrawableObjects();
    auto update = [ds = update_delta_seconds] (auto&&... bindings)
    {
        ((bindings.view.Update(ds)), ...);
    };

    std::apply(update, mVVMBindings);
}

} // namespace open_labora

#endif // GAMESTATE_HPP_
