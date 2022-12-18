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

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include "IGameWindow.hpp"

namespace open_labora
{

namespace gui
{

constexpr auto kRegularTextRatio{ 16.f / 1080 };
constexpr auto kBigTextRatio{ 20.f / 1080 };

constexpr auto kMargin = 4;

constexpr int getRegularTextSize(int window_height)
{
    return static_cast<int>(window_height * kRegularTextRatio);
}

constexpr int getBigTextSize(int window_height)
{
    return static_cast<int>(window_height * kBigTextRatio);
}

template<typename TSizeGetter>
concept CSizeGetter = requires (TSizeGetter get_size, int window_height)
{
    std::invoke(get_size, window_height);
};

template<CSizeGetter TGetSize>
void setDynamicTextSize(Widget::Ptr widget,
                        IGameWindow::Ptr game_window,
                        TGetSize get_size)
{
    auto set_size =
    [get_size,
     widget = std::weak_ptr<Widget>{ widget },
     game_window = std::weak_ptr<IGameWindow>{ game_window }]
    {
        assert(!widget.expired());
        assert(!game_window.expired());
        auto window_height = game_window.lock()->GetWindowSize().y;
        widget.lock()->setTextSize(std::invoke(get_size, window_height));
    };
    widget->onSizeChange(set_size);
}

} // namespace gui

} // namespace open_labora

#endif // COMMON_HPP_
