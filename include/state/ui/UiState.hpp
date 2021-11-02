#ifndef UISTATE_HPP_
#define UISTATE_HPP_

#include <vector>
#include <SFGUI/Widget.hpp>
#include "state/BaseState.hpp"

class UiState : public BaseState
{
protected:
    std::vector<sfg::Widget::Ptr> mUiObjects;
public:
    UiState(State& state) : BaseState{ state } {};
    virtual ~UiState() override = default;
};

#endif // UISTATE_HPP_
