#ifndef UISTATE_HPP_
#define UISTATE_HPP_

#include <vector>
#include <SFGUI/Widget.hpp>
#include "state/BaseState.hpp"
#include "state/State.hpp"

class Renderer;

namespace sfg {
    class Desktop;
}

class UiState : public BaseState
{
protected:
    std::vector<sfg::Widget::Ptr> mWidgets;
    Renderer& GetRenderer() & noexcept;
    sfg::Desktop& GetDesktop() & noexcept;
    void AddWidgetToDesktop(sfg::Widget::Ptr);
    void RemoveAllWidgets();
public:
    UiState(State& state) : BaseState{ state } {};
    virtual ~UiState() override { RemoveAllWidgets(); }
};

#endif // UISTATE_HPP_
