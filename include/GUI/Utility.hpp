#ifndef UTILITY_HPP_
#define UTILITY_HPP_

#include <SFGUI/Widget.hpp>

namespace OpenLabora
{

// Connects delegate to specified widget's signal
inline uint32_t connect(sfg::Widget::Ptr widget,
             sfg::Signal::SignalID& signal,
             std::function<void()> delegate)
{
    return static_cast<uint32_t>(widget->GetSignal(signal).Connect(delegate));
}

} // namespace OpenLabora

#endif // UTILITY_HPP_
