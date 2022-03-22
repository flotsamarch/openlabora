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
    using ViewPtr = typename TView::Ptr;
    using ControllerPtr = typename TController::Ptr;

public:
    using ModelT = TModel;
    using ViewT = TView;
    using ControllerT = TController;

    ModelPtr model;
    ControllerPtr controller;
    ViewPtr view;

    AppState(ModelPtr _model, ViewPtr _view, ControllerPtr _controller)
        : model{ _model }, controller{ _controller }, view{ std::move(_view) } {}
};

} // namespace OpenLabora

#endif // APPSTATE_HPP_
