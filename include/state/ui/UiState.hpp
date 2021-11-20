#ifndef UISTATE_HPP_
#define UISTATE_HPP_

#include <vector>
#include <SFGUI/Widget.hpp>
#include "state/BaseState.hpp"
#include "IRenderer.hpp"
#include "GUI/IDesktop.hpp"

class State;

// General UI logic base class
class UiState : public BaseState
{
protected:
    std::vector<sfg::Widget::Ptr> mWidgets;

    IRenderer* GetRenderer() const;

    IDesktop& GetDesktop() &;

    void AddWidgetToDesktop(sfg::Widget::Ptr);

    // Remove all widgets that are created by THIS instance
    void RemoveAllWidgets();
public:
    UiState(std::shared_ptr<State> state) : BaseState{ state } {};

    ~UiState() noexcept;
};

#endif // UISTATE_HPP_
