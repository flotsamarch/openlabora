#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <SFGUI/Widget.hpp>
#include <GameState/Controllers/GameController.hpp>

namespace OpenLabora
{

template<typename T>
concept CWidget = std::derived_from<T, sfg::Widget>;

// Connects delegate to specified widget's signal
inline uint32_t connect(sfg::Widget::Ptr widget,
                        sfg::Signal::SignalID& signal,
                        std::function<void()> delegate)
{
    return static_cast<uint32_t>(widget->GetSignal(signal).Connect(delegate));
}

// Factory function to create widgets that prevent mouse events from
// propagating into gameplay layer
template<CWidget TWidget, typename... Args>
typename TWidget::Ptr CreateEventConsumingWidget(GameController::WPtr ctlr,
                                                 Args&&... args)
{
    auto widget = TWidget::Create(std::forward<Args>(args)...);

    auto mouse_left_release_handled =
    [ctlr]
    {
        assert(!ctlr.expired());
        ctlr.lock()->IgnoreNextEvent(sf::Event::MouseButtonReleased);
    };

    connect(widget,
            sfg::Widget::OnMouseLeftRelease,
            mouse_left_release_handled);

    if constexpr (std::derived_from<TWidget, sfg::Window>) {
        connect(widget,
                sfg::Window::OnCloseButton,
                mouse_left_release_handled);
    }

    return widget;
};


} // namespace OpenLabora

#endif // UTILITY_HPP_
