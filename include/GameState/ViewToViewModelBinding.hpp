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

#ifndef VIEWTOVIEWMODELBINDING_HPP_
#define VIEWTOVIEWMODELBINDING_HPP_

#include <memory>
#include "Views/ViewConcept.hpp"

namespace open_labora
{

class ApplicationContext;
struct IGameWindow;

// Uniform initializer of a view-to-viewmodel binding
template<class TModel>
struct BindingInitializer final
{
    PtrView<ApplicationContext> app;
    std::shared_ptr<IGameWindow> game_window;
    PtrView<TModel> model;

    BindingInitializer(PtrView<ApplicationContext> _app,
                       std::shared_ptr<IGameWindow> _window,
                       PtrView<TModel> _model)
        : app{ _app },
          game_window{ _window },
          model{ _model } {};
};

// Structure that holds a single pair of a View and its corresponding ViewModel
template<class TModel, CView TView, class TViewModel>
struct ViewToViewModelBinding
{
    TView view;
    TViewModel view_model;

    ViewToViewModelBinding(BindingInitializer<TModel> init)
        : view{ init.app, init.game_window, PtrView{ &view_model } },
          view_model{ init.model } {};
};

// Helper metaclass for simple declarations of view-viewmodel bindings
template<class TModel,
         template<class...> class TView,
         template<class...> class TViewModel>
struct VVMBindingHelper
{
    using ViewModel = TViewModel<TModel>;
    using View = TView<ViewModel>;
    using Binding = ViewToViewModelBinding<TModel, View, ViewModel>;
};

// Using statement for simple declarations of view-viewmodel bindings
template<class TModel,
         template<class...> class TView,
         template<class...> class TViewModel>
using VVMBinding = typename VVMBindingHelper<TModel, TView, TViewModel>::Binding;

} // namespace open_labora

#endif // VIEWTOVIEWMODELBINDING_HPP_
