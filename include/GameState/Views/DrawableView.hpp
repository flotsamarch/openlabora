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

#ifndef DRAWABLEVIEW_HPP_
#define DRAWABLEVIEW_HPP_

#include "ApplicationState/ApplicationContext.hpp"
#include "IGameWindow.hpp"
#include "Input/Input.hpp"

namespace open_labora
{

/**
 * Fills drawable container with references to drawable objects.
 *
 * Must appear in bindings list after all other view/view-models that could
 * modify entity registry in their Update(...) method.
 */
template<class TViewModel>
class DrawableView final
{
    PtrView<TViewModel> mViewModel;

public:
    DrawableView(ApplicationContext::Ptr,
                 IGameWindow::Ptr,
                 PtrView<TViewModel> view_model)
        : mViewModel{ view_model } {}

    bool HandleInput(Input::PtrConst)
    {
        return false;
    }

    void Update(float update_delta_seconds);
};

template<class TViewModel>
void DrawableView<TViewModel>::Update([[maybe_unused]]float update_delta_seconds)
{
    mViewModel->FillDrawableContainer();
};


} // open_laboraspace open_labora

#endif // DRAWABLEVIEW_HPP_
