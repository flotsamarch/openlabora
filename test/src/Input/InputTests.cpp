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

#include <gtest/gtest.h>
#include <SFML/Window/Window.hpp>
#include "Input/Input.hpp"

namespace test
{

namespace ol = open_labora;

TEST(InputTests, NoUnhanledInputByDefault)
{
    auto input = ol::Input{};

    ASSERT_FALSE(input.HasUnhandledInput());
}

TEST(InputTests, HandleEvent_ProducesUnhanledInput)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::KeyPressed;
    input.HandleEvent(event);

    ASSERT_TRUE(input.HasUnhandledInput());
}

TEST(InputTests, HandleEvent_BadEventProducesNoInput)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::GainedFocus;
    input.HandleEvent(event);

    ASSERT_FALSE(input.HasUnhandledInput());
}

TEST(InputTests, Advance_NoInput)
{
    auto input = ol::Input{};

    input.Advance();

    ASSERT_FALSE(input.HasUnhandledInput());
}

TEST(InputTests, Advance_PopsInput)
{
    auto input = ol::Input{};
    auto event = sf::Event{};
    event.type = sf::Event::KeyPressed;

    input.HandleEvent(event);
    input.Advance();

    ASSERT_FALSE(input.HasUnhandledInput());
}

TEST(InputTests, IsButtonDown_NotDownByDefault)
{
    auto input = ol::Input{};

    ASSERT_FALSE(input.IsButtonDown(ol::input::Button::MouseLeft));
}

TEST(InputTests, IsButtonDown_DownAfterClick)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);

    ASSERT_TRUE(input.IsButtonDown(ol::input::Button::MouseLeft));
}

TEST(InputTests, IsButtonDown_NotDownAfterRelease)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::MouseButtonReleased;
    input.HandleEvent(event);

    ASSERT_FALSE(input.IsButtonDown(ol::input::Button::MouseLeft));
}

TEST(InputTests, IsButtonDown_TwoKeysDoNotInterfere)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Q;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();

    EXPECT_FALSE(input.IsButtonDown(ol::input::Button::MouseLeft));
    ASSERT_TRUE(input.IsButtonDown(ol::input::Button::Q));
}

TEST(InputTests, HasButtonBeenPressed_TrueAfterClick)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);

    ASSERT_TRUE(input.HasButtonBeenPressed(ol::input::Button::MouseLeft));
}

TEST(InputTests, HasButtonBeenPressed_FalseAfterAdvance)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();

    ASSERT_FALSE(input.HasButtonBeenPressed(ol::input::Button::MouseLeft));
}

TEST(InputTests, HasButtonBeenPressed_FalseAfterRelease)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::MouseButtonReleased;
    input.HandleEvent(event);

    ASSERT_FALSE(input.HasButtonBeenPressed(ol::input::Button::MouseLeft));
}

TEST(InputTests, HasButtonBeenPressed_TwoKeysDoNotInterfere)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Q;
    input.HandleEvent(event);

    EXPECT_FALSE(input.HasButtonBeenPressed(ol::input::Button::MouseLeft));
    ASSERT_TRUE(input.HasButtonBeenPressed(ol::input::Button::Q));
}

TEST(InputTests, HasButtonBeenReleased_FalseAfterClick)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);

    ASSERT_FALSE(input.HasButtonBeenReleased(ol::input::Button::MouseLeft));
}

TEST(InputTests, HasButtonBeenReleased_TrueAfterRelease)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::MouseButtonReleased;
    input.HandleEvent(event);

    ASSERT_TRUE(input.HasButtonBeenReleased(ol::input::Button::MouseLeft));
}

TEST(InputTests, HasButtonBeenReleased_FalseAfterAdvance)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::MouseButtonReleased;
    input.HandleEvent(event);
    input.Advance();

    ASSERT_FALSE(input.HasButtonBeenReleased(ol::input::Button::MouseLeft));
}

TEST(InputTests, HasButtonBeenReleased_TwoKeysDoNotInterfere)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Q;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    event.type = sf::Event::KeyReleased;
    event.key.code = sf::Keyboard::Q;
    input.HandleEvent(event);

    EXPECT_FALSE(input.HasButtonBeenReleased(ol::input::Button::MouseLeft));
    ASSERT_TRUE(input.HasButtonBeenReleased(ol::input::Button::Q));
}

TEST(InputTests, GetButtonHoldDurationAsSeconds_ButtonPressed)
{
    constexpr auto left = ol::input::Button::MouseLeft;
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);

    ASSERT_FLOAT_EQ(input.GetButtonHoldDurationAsSeconds(left), 0);
}

TEST(InputTests, GetButtonHoldDurationAsSeconds_ButtonHeld)
{
    constexpr auto left = ol::input::Button::MouseLeft;
    constexpr auto duration = 1.f;
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    input.Update(duration);

    ASSERT_GE(input.GetButtonHoldDurationAsSeconds(left), duration);
}

TEST(InputTests, GetButtonHoldDurationAsSeconds_Released)
{
    constexpr auto left = ol::input::Button::MouseLeft;
    constexpr auto duration = 1.f;
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    input.Update(duration);
    event.type = sf::Event::MouseButtonReleased;
    input.HandleEvent(event);

    ASSERT_LT(input.GetButtonHoldDurationAsSeconds(left), 0.f);
}

TEST(InputTests, GetButtonHoldDurationAsSeconds_TwoKeysDoNotInterfere)
{
    constexpr auto left = ol::input::Button::MouseLeft;
    constexpr auto q = ol::input::Button::Q;
    constexpr auto duration = 1.f;
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    input.HandleEvent(event);
    input.Advance();
    input.Update(duration); // updates LMB
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Q;
    input.HandleEvent(event);
    input.Advance();
    input.Update(duration); // updates LMB + Q

    ASSERT_GE(input.GetButtonHoldDurationAsSeconds(q), duration);
    ASSERT_GE(input.GetButtonHoldDurationAsSeconds(left), duration * 2);
}

TEST(InputTests, IsMouseMoving_FalseByDefault)
{
    auto input = ol::Input{};

    ASSERT_FALSE(input.IsMouseMoving());
}

TEST(InputTests, IsMouseMoving_TrueAfterMouseMoved)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseMoved;
    input.HandleEvent(event);

    ASSERT_TRUE(input.IsMouseMoving());
}

TEST(InputTests, IsMouseMoving_FalseAfterAdvance)
{
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseMoved;
    input.HandleEvent(event);
    input.Advance();

    ASSERT_FALSE(input.IsMouseMoving());
}

TEST(InputTests, GetMousePosition)
{
    constexpr auto position_x = 777;
    constexpr auto position_y = 555;
    auto input = ol::Input{};
    auto event = sf::Event{};

    auto initial_position = input.GetMousePosition();

    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = position_x;
    event.mouseMove.y = position_y;
    input.HandleEvent(event);

    auto new_position = input.GetMousePosition();

    EXPECT_NE(initial_position, new_position);
    EXPECT_EQ(new_position.x, position_x);
    ASSERT_EQ(new_position.y, position_y);
}

TEST(InputTests, GetMouseMovedOffset_ZeroByDefault)
{
    auto input = ol::Input{};

    auto offset = input.GetMouseMoveOffset();

    EXPECT_EQ(offset.x, 0);
    ASSERT_EQ(offset.y, 0);
}

TEST(InputTests, GetMouseMovedOffset_MouseMoved)
{
    constexpr auto position_x = 11;
    constexpr auto position_y = 232;
    auto input = ol::Input{};
    auto event = sf::Event{};

    auto initial_position = input.GetMousePosition();

    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = position_x;
    event.mouseMove.y = position_y;
    input.HandleEvent(event);

    auto offset = input.GetMouseMoveOffset();

    EXPECT_EQ(offset.x, position_x - initial_position.x);
    ASSERT_EQ(offset.y, position_y - initial_position.y);
}

TEST(InputTests, GetMouseMovedOffset_ZeroAfterAdvance)
{
    constexpr auto offset_x = 121;
    constexpr auto offset_y = 32;
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = offset_x;
    event.mouseMove.y = offset_y;
    input.HandleEvent(event);
    input.Advance();

    auto offset = input.GetMouseMoveOffset();

    EXPECT_EQ(offset.x, 0);
    ASSERT_EQ(offset.y, 0);
}

TEST(InputTests, GetScrollDelta_ZeroByDefault)
{
    auto input = ol::Input{};

    auto offset = input.GetScrollDelta();

    ASSERT_FLOAT_EQ(offset, 0.f);
}

TEST(InputTests, GetScrollDelta_NonZeroAfterScroll)
{
    constexpr float delta = 8.f;
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseWheelScrolled;
    event.mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;
    event.mouseWheelScroll.delta = delta;
    input.HandleEvent(event);

    ASSERT_FLOAT_EQ(input.GetScrollDelta(), delta);
}

TEST(InputTests, GetScrollDelta_ZeroAfterAdvance)
{
    constexpr float delta = 18.f;
    auto input = ol::Input{};
    auto event = sf::Event{};

    event.type = sf::Event::MouseWheelScrolled;
    event.mouseWheelScroll.wheel = sf::Mouse::VerticalWheel;
    event.mouseWheelScroll.delta = delta;
    input.HandleEvent(event);
    input.Advance();

    ASSERT_FLOAT_EQ(input.GetScrollDelta(), 0);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
