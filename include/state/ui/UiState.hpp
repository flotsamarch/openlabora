#ifndef UISTATE_HPP_
#define UISTATE_HPP_

#include <memory>
#include <vector>
#include <SFGUI/Widget.hpp>
#include "state/ui/IUiState.hpp"

class State;

// General UI logic base class
class UiState : public IUiState
{
protected:
    std::weak_ptr<State> mState;
    std::vector<sfg::Widget::Ptr> mWidgets;

protected:
    IRenderer& GetRenderer() const & override final;

    void AddWidgetToDesktop(sfg::Widget::Ptr) override final;

    void RemoveAllWidgets() override final;

public:
    UiState(std::shared_ptr<State> state) : mState{ state } {};

    inline ~UiState() noexcept = 0;

    void HandleEvent(const sf::Event&) override {};

    void HandleEventImpl(const sf::Event&) override {};

    void Update([[maybe_unused]]const float seconds) override {};
};

inline UiState::~UiState() noexcept
{
    try {
        RemoveAllWidgets();
    }
    catch (std::runtime_error&) {}
}

#endif // UISTATE_HPP_
