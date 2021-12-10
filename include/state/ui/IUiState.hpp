#ifndef IUISTATE_HPP_
#define IUISTATE_HPP_

#include "state/ILogicState.hpp"
#include "IRenderer.hpp"
#include "GUI/IDesktop.hpp"

class IUiState : virtual public ILogicState
{
    virtual IRenderer& GetRenderer() const & = 0;

    virtual IDesktop& GetDesktop() & = 0;

    virtual void AddWidgetToDesktop(sfg::Widget::Ptr) = 0;

    // Remove all widgets that are created by THIS instance
    virtual void RemoveAllWidgets() = 0;
};

#endif // IUISTATE_HPP_
