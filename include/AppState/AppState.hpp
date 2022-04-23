#ifndef APPSTATE_HPP_
#define APPSTATE_HPP_

#include "GameState/Model/Model.hpp"

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
    using ViewPtr = typename TView::Ptr;
    using ControllerPtr = typename TController::Ptr;

public:
    using ModelType = TModel;
    using ViewType = TView;
    using ControllerType = TController;

    ModelPtr model;
    ViewPtr view;
    ControllerPtr controller;

    AppState(ModelPtr _model, ViewPtr _view, ControllerPtr _controller)
        : model{ _model }, view{ std::move(_view) }, controller{ _controller } {}
};

} // namespace OpenLabora

#endif // APPSTATE_HPP_
