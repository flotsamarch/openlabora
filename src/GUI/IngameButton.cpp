#include <cassert>
#include "GUI/IngameButton.hpp"

namespace OpenLabora
{

IngameButton::IngameButton(IGameView& view)
    : mGameView{ view } {}

IngameButton::Ptr IngameButton::Create(IGameView& view,
                                       const sf::String& label)
{
    auto btn = Ptr(new IngameButton{ view });
    btn->SetLabel(label);

    btn->GetSignal(sfg::Widget::OnMouseEnter).Connect(
    [&view]
    {
        // TODO set flag in model
        // auto&& state = static_cast<GSCommon&>(state_ptr.lock()->GetGameState());
        // state.SetMouseCapturedFlag(true);
    });

    btn->GetSignal(sfg::Widget::OnMouseLeave).Connect(
    [&view]
    {
        // TODO unset flag in model
        // auto&& state = static_cast<GSCommon&>(state_ptr.lock()->GetGameState());
        // state.SetMouseCapturedFlag(false);
    });

    return btn;
}

} // namespace OpenLabora
