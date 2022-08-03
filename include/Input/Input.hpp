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

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <queue>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <SFML/Window/Event.hpp>
#include "LibTypedefs.hpp"
#include "Misc/PtrView.hpp"

namespace open_labora
{

namespace input
{

enum class Button
{
    Unknown = -1,
    A = 0, B, C,
    D, E, F, G,
    H, I, J, K,
    L, M, N, O,
    P, Q, R, S,
    T, U, V, W,
    X, Y, Z,
    Key0, Key1, Key2,
    Key3, Key4, Key5,
    Key6, Key7, Key8,
    Key9,
    Escape, LControl, LShift,
    LAlt, LSystem, RControl,
    RShift, RAlt, RSystem,
    Menu, LBracket, RBracket,
    Semicolon, Comma, Period,
    Quote, Slash, Backslash,
    Tilde, Equal, Hyphen,
    Space, Enter, Backspace,
    Tab, PageUp, PageDown,
    End, Home, Insert,
    Delete, Add, Subtract,
    Multiply, Divide, Left,
    Right, Up, Down,
    Numpad0, Numpad1, Numpad2,
    Numpad3, Numpad4, Numpad5,
    Numpad6, Numpad7, Numpad8,
    Numpad9,
    F1, F2, F3,
    F4, F5, F6,
    F7, F8, F9,
    F10, F11, F12,
    F13, F14, F15,
    Pause,
    MouseLeft,
    MouseRight,
    MouseMiddle,
    MouseX1,
    MouseX2,
    Count
};

// Since key is an enum - find(...) is very close to O(1)
inline const std::unordered_set<sf::Event::EventType> kInputEventList
{
    sf::Event::EventType::KeyPressed,
    sf::Event::EventType::KeyReleased,
    sf::Event::EventType::MouseButtonPressed,
    sf::Event::EventType::MouseButtonReleased,
    sf::Event::EventType::MouseMoved,
    sf::Event::EventType::MouseWheelScrolled,
};

} // namespace input

/**
 * Time machine for buffered keyboard and mouse input. When current state has
 * been processed it should be advanced to the next one until the buffer is empty
 */
class Input
{
    struct ButtonState
    {
        static constexpr float kNotDown = -1.f;

    private:
        float mHoldDuration{ kNotDown };

    public:
        bool IsDown() const noexcept { return mHoldDuration >= 0; }

        void SetDown(bool is_down) noexcept
        { mHoldDuration =  is_down ? 0.f : kNotDown; }

        void Update(float update_delta_seconds) noexcept
        { mHoldDuration += update_delta_seconds; }

        float GetHoldDurationAsSeconds() const noexcept
        { return mHoldDuration; }
    };

    using Button = input::Button;
    std::queue<sf::Event> mEvents;
    std::unordered_map<Button, ButtonState> mButtons;

    Vector2i mMousePosition{ sf::Mouse::getPosition() };

    void Pop();

    void OnNewEventAtQueueFront();

public:
    using Ptr = PtrView<Input>;

    using PtrConst = PtrView<const Input>;

    bool IsButtonDown(Button) const;

    bool HasButtonBeenPressed(Button) const;

    bool HasButtonBeenReleased(Button) const;

    float GetButtonHoldDurationAsSeconds(Button) const;

    bool IsMouseMoving() const noexcept;

    Vector2i GetMouseMoveOffset() const;

    Vector2i GetMousePosition() const;

    float GetScrollDelta() const;

    bool HasUnhandledInput() const noexcept { return !mEvents.empty(); }

    void HandleEvent(const sf::Event&);

    void Advance() { Pop(); }

    void Update(float update_delta_seconds) noexcept;
};

} // namespace open_labora

#endif // INPUT_HPP_
