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
#include <gmock/gmock.h>
#include <TGUI/Backends/SFML.hpp>
#include "GUI/ExpansionWindow.hpp"
#include "RendererDependenciesMocks.hpp"

namespace test
{

namespace ol = open_labora;

constexpr uint32_t win_size_x{ 1920 };
constexpr uint32_t win_size_y{ 1080 };

class ExpansionWindowTests : public ::testing::Test
{
    using WindowMock = sf::RenderTexture;
    using Gui = tgui::GuiSFML;
    using GameWindow = ol::GameWindow<Gui, WindowMock>;
    WindowMock mWindow{};
    Gui mGui{};

protected:
    GameWindow mGameWindow{ ol::PtrView{ &mGui }, ol::PtrView{ &mWindow } };
    ol::ExpansionWindow mExpansionWindow{ mGameWindow };

public:
    ExpansionWindowTests()
    {
        mWindow.create(1920, 1080);
        mGui.setTarget(mWindow);
    }
};

TEST_F(ExpansionWindowTests, GetWindow_NotNull)
{
    auto window = mExpansionWindow.GetWindow();

    ASSERT_NE(window, nullptr);
}

TEST_F(ExpansionWindowTests, GetWindow_IsCentered)
{
    constexpr auto center = 0.5f;
    auto window = mExpansionWindow.GetWindow();

    auto origin = window->getOrigin();
    auto position = window->getPosition();

    EXPECT_FLOAT_EQ(origin.x, center);
    EXPECT_FLOAT_EQ(origin.y, center);
    EXPECT_FLOAT_EQ(position.x, win_size_x / 2.f);
    EXPECT_FLOAT_EQ(position.y, win_size_y / 2.f);
}

TEST_F(ExpansionWindowTests, GetWindow_HasChildren)
{
    auto window = mExpansionWindow.GetWindow();

    ASSERT_NE(window->getWidgets().size(), 0);
}

TEST_F(ExpansionWindowTests, GetWindow_IsNotVisible)
{
    auto window = mExpansionWindow.GetWindow();

    ASSERT_FALSE(window->isVisible());
}

TEST_F(ExpansionWindowTests, GetConfirmButton_NotNull)
{
    auto button = mExpansionWindow.GetConfirmButton();

    ASSERT_NE(button, nullptr);
}

TEST_F(ExpansionWindowTests, GetDeclineButton_NotNull)
{
    auto button = mExpansionWindow.GetDeclineButton();

    ASSERT_NE(button, nullptr);
}

TEST_F(ExpansionWindowTests, SetState_ChooseOne_TogglesExist)
{
    mExpansionWindow.SetState(ol::expansionWindow::StateChooseOne{});
    const auto name_1 = ol::expansionWindow::kAltToggle1Name;
    const auto name_2 = ol::expansionWindow::kAltToggle2Name;

    auto window = mExpansionWindow.GetWindow();
    auto toggle_1 = window->get<tgui::ToggleButton>(name_1);
    auto toggle_2 = window->get<tgui::ToggleButton>(name_2);

    EXPECT_NE(toggle_1, nullptr);
    EXPECT_NE(toggle_2, nullptr);
}

TEST_F(ExpansionWindowTests, SetState_Confirm_TogglesDoNotExist)
{
    mExpansionWindow.SetState(ol::expansionWindow::StateConfirm{});
    const auto name_1 = ol::expansionWindow::kAltToggle1Name;
    const auto name_2 = ol::expansionWindow::kAltToggle2Name;

    auto window = mExpansionWindow.GetWindow();
    auto toggle_1 = window->get<tgui::ToggleButton>(name_1);
    auto toggle_2 = window->get<tgui::ToggleButton>(name_2);

    EXPECT_EQ(toggle_1, nullptr);
    EXPECT_EQ(toggle_2, nullptr);
}

TEST_F(ExpansionWindowTests, Show_SetsWindowVisible)
{
    mExpansionWindow.Show(true);
    auto window = mExpansionWindow.GetWindow();

    ASSERT_TRUE(window->isVisible());
}

TEST_F(ExpansionWindowTests, Show_SetsWindowNotVisible)
{
    mExpansionWindow.Show(true);
    mExpansionWindow.Show(false);
    auto window = mExpansionWindow.GetWindow();

    ASSERT_FALSE(window->isVisible());
}

TEST_F(ExpansionWindowTests, GetToggleValue_ZeroByDefault)
{
    mExpansionWindow.SetState(ol::expansionWindow::StateChooseOne{});
    auto value = mExpansionWindow.GetToggleValue();

    ASSERT_EQ(value, 0);
}

TEST_F(ExpansionWindowTests, GetToggleValue_ToggleButtonOne)
{
    mExpansionWindow.SetState(ol::expansionWindow::StateChooseOne{});
    const auto name = ol::expansionWindow::kAltToggle1Name;
    auto window = mExpansionWindow.GetWindow();
    auto toggle = window->get<tgui::ToggleButton>(name);

    toggle->setDown(true);
    auto value = mExpansionWindow.GetToggleValue();

    ASSERT_EQ(value, 1);
}

TEST_F(ExpansionWindowTests, GetToggleValue_ToggleButtonTwo)
{
    mExpansionWindow.SetState(ol::expansionWindow::StateChooseOne{});
    const auto name = ol::expansionWindow::kAltToggle2Name;
    auto window = mExpansionWindow.GetWindow();
    auto toggle = window->get<tgui::ToggleButton>(name);

    toggle->setDown(true);
    auto value = mExpansionWindow.GetToggleValue();

    ASSERT_EQ(value, 2);
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
