#include <cassert>
#include "GUI/IngameButton.hpp"
#include "state/gs/GSCommon.hpp"

IngameButton::Ptr IngameButton::Create(std::shared_ptr<::State> state,
                                      const sf::String& label)
{
    auto btn = Ptr(new IngameButton);
    btn->SetLabel(label);
    btn->mState = state;

    btn->GetSignal(sfg::Widget::OnMouseEnter).Connect(
    [state_ptr = btn->mState]
    {
        assert(!state_ptr.expired());
        auto&& state = static_cast<GSCommon&>(state_ptr.lock()->GetGameState());
        state.SetMouseCapturedFlag(true);
    });

    btn->GetSignal(sfg::Widget::OnMouseLeave).Connect(
    [state_ptr = btn->mState]
    {
        assert(!state_ptr.expired());
        auto&& state = static_cast<GSCommon&>(state_ptr.lock()->GetGameState());
        state.SetMouseCapturedFlag(false);
    });

    return btn;
}
