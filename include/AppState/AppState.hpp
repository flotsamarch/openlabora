#ifndef APPSTATE_HPP_
#define APPSTATE_HPP_

#include "GameState/Model.hpp"

#include "GameState/Views/GVMainMenu.hpp"
#include "GameState/Views/GVDuel.hpp"
#include "GameState/Views/GVFinal.hpp"

#include "GameState/Controllers/GCMainMenu.hpp"
#include "GameState/Controllers/GCDuel.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

// Represents a state of the application with the help of MVC pattern
template<class TModel, class TView, class TController>
class AppState final
{
    using ModelPtr = typename TModel::Ptr;
    using ControllerPtr = typename TController::Ptr;

public:
    using ModelT = TModel;
    using ViewT = TView;
    using ControllerT = TController;

    ModelPtr model;
    ControllerPtr controller;
    TView view;

    AppState(ModelPtr _model, TView _view, ControllerPtr _controller)
        : model{ _model }, controller{ _controller }, view{ _view } {}
};

// ----------------------- ADD ALL STATES HERE ----------------------------------
using MainMenuState = AppState<NoModel, GVMainMenu, GCMainMenu>;
using DuelState = AppState<Model, GVDuel, GCDuel>;
using FinalState = AppState<NoModel, GVFinal, GCFinal>;

using State = std::variant<MainMenuState, DuelState, FinalState>;

} // namespace OpenLabora

#endif // APPSTATE_HPP_
