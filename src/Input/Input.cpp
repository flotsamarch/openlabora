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

#include "Input/Input.hpp"

namespace open_labora
{

using input::Button;

namespace
{

Button convertButtonFromSfml(sf::Mouse::Button code) noexcept
{
    constexpr auto mouse_first_code = static_cast<int>(Button::MouseLeft);
    return static_cast<Button>(static_cast<int>(code) + mouse_first_code);
}

Button convertKeyFromSfml(sf::Keyboard::Key code) noexcept
{
    return static_cast<Button>(code);
}

} // namespace anonymous

void Input::Pop()
{
    if (mEvents.empty()) {
        return;
    }

    auto&& event = mEvents.front();

    if (event.type == sf::Event::MouseMoved) {
        mMousePosition = { event.mouseMove.x, event.mouseMove.y };
    }

    mEvents.pop();

    if (!mEvents.empty()) {
        OnNewEventAtQueueFront();
    }
}

void Input::OnNewEventAtQueueFront()
{
    if (mEvents.empty()) {
        return;
    }

    auto&& event = mEvents.front();

    switch (event.type) {
        case sf::Event::KeyPressed:
        {
            auto button = convertKeyFromSfml(event.key.code);
            mButtons[button].SetDown(true);
            break;
        }
        case sf::Event::KeyReleased:
        {
            auto button = convertKeyFromSfml(event.key.code);
            mButtons[button].SetDown(false);
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            auto button = convertButtonFromSfml(event.mouseButton.button);
            mButtons[button].SetDown(true);
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            auto button = convertButtonFromSfml(event.mouseButton.button);
            mButtons[button].SetDown(false);
            break;
        }
        default:
        {
        }
    }
}

bool Input::IsButtonDown(Button button) const
{
    auto it = mButtons.find(button);
    if (it == mButtons.end()) {
        return false;
    }

    return it->second.IsDown();
}

bool Input::HasButtonBeenPressed(Button button) const
{
    if (mEvents.empty()) {
        return false;
    }

    auto&& event = mEvents.front();
    bool mouse_pressed = event.type == sf::Event::MouseButtonPressed;
    bool keyboard_pressed = event.type == sf::Event::KeyPressed;

    if (!mouse_pressed && !keyboard_pressed) {
        return false;
    }

    if (mouse_pressed) {
        return convertButtonFromSfml(event.mouseButton.button) == button;
    }

    if (keyboard_pressed) {
        return convertKeyFromSfml(event.key.code) == button;
    }

    return false;
}

bool Input::HasButtonBeenReleased(Button button) const
{
    if (mEvents.empty()) {
        return false;
    }

    auto&& event = mEvents.front();
    bool mouse_released = event.type == sf::Event::MouseButtonReleased;
    bool keyboard_released = event.type == sf::Event::KeyReleased;

    if (!mouse_released && !keyboard_released) {
        return false;
    }

    if (mouse_released) {
        return convertButtonFromSfml(event.mouseButton.button) == button;
    }

    if (keyboard_released) {
        return convertKeyFromSfml(event.key.code) == button;
    }

    return false;
}

float Input::GetButtonHoldDurationAsSeconds(Button button) const
{
    auto it = mButtons.find(button);
    if (it == mButtons.end()) {
        return ButtonState::kNotDown;
    }

    return it->second.GetHoldDurationAsSeconds();
}

bool Input::IsMouseMoving() const noexcept
{
    return !mEvents.empty() && mEvents.front().type == sf::Event::MouseMoved;
}

Vector2i Input::GetMouseMoveOffset() const
{
    if (mEvents.empty()) {
        return {};
    }

    auto&& event = mEvents.front();
    if (event.type != sf::Event::MouseMoved) {
        return {};
    }

    const auto dx = event.mouseMove.x - mMousePosition.x;
    const auto dy = event.mouseMove.y - mMousePosition.y;
    return { dx, dy };
}

Vector2i Input::GetMousePosition() const
{
    if (mEvents.empty() || mEvents.front().type != sf::Event::MouseMoved) {
        return mMousePosition;
    }

    auto&& event = mEvents.front();
    return { event.mouseMove.x , event.mouseMove.y };
}

float Input::GetScrollDelta() const
{
    if (mEvents.empty()) {
        return {};
    }

    auto&& event = mEvents.front();
    if (event.type != sf::Event::MouseWheelScrolled) {
        return 0.f;
    }

    if (event.mouseWheelScroll.wheel != sf::Mouse::VerticalWheel) {
        return 0.f;
    }

    return event.mouseWheelScroll.delta;
}

void Input::Update(float update_delta_seconds) noexcept
{
    for (auto&& [_, button] : mButtons) {
        if (button.IsDown()) {
            button.Update(update_delta_seconds);
        }
    }
}

void Input::HandleEvent(const sf::Event& event)
{
    const auto type = event.type;
    if (input::kInputEventList.find(type) == input::kInputEventList.end()) {
        return;
    }

    mEvents.push(event);

    if (mEvents.size() == 1) {
        OnNewEventAtQueueFront();
    }
}

} // namespace open_labora
