#ifndef APPSTATE_HPP_
#define APPSTATE_HPP_

#include <memory>

namespace OpenLabora
{

// Represents a state of the application
template<class TView, class TController>
struct AppState final
{

    std::shared_ptr<TController> controller;
    TView view;

    AppState(typename TController::Ptr _controller, TView _view)
        : controller{ _controller }, view{ _view } {}
};

} // namespace OpenLabora

#endif // APPSTATE_HPP_
