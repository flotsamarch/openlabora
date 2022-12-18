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
#include "GUI/ConfirmationWindow.hpp"
#include "GameWindowMock.hpp"

namespace test
{

using testing::NiceMock;
using testing::Return;
using testing::_;

constexpr auto kDefaultWidth = 1;
constexpr auto kDefaultHeight = 1;

namespace
{

tgui::GuiSFML _gui; // Required to create GUI objects

} // namespace anonymous

class ConfirmationWindowTestsBase : public testing::Test
{
    using TestGameWindow = NiceMock<GameWindowMock>;
    using TestGameWindowPtr = std::shared_ptr<TestGameWindow>;

protected:
    TestGameWindowPtr mGameWindow = std::make_shared<TestGameWindow>();

    inline static const auto kDefaultWindowSize =
        ol::Vector2i{ kDefaultWidth, kDefaultHeight };

    ConfirmationWindowTestsBase()
    {
        ON_CALL(*mGameWindow, GetWindowSize)
            .WillByDefault(Return(kDefaultWindowSize));
    }
};

class ConfirmationWindowTests : public ConfirmationWindowTestsBase
{
protected:
    ol::ConfirmationWindow mWindow{ mGameWindow, kDefaultWidth, kDefaultHeight };
};

TEST_F(ConfirmationWindowTestsBase, ConstructorRequestsGameWindowSize)
{
    EXPECT_CALL(*mGameWindow, GetWindowSize)
        .WillOnce(Return(kDefaultWindowSize));

    ol::ConfirmationWindow mWindow{ mGameWindow, kDefaultWidth, kDefaultHeight };
}

TEST_F(ConfirmationWindowTestsBase, ConstructorAddsWidgets)
{
    EXPECT_CALL(*mGameWindow, AddWidget(_))
        .Times(testing::AtLeast(1));

    ol::ConfirmationWindow mWindow{ mGameWindow, kDefaultWidth, kDefaultHeight };
}

TEST_F(ConfirmationWindowTestsBase, GetWindowSize)
{
    constexpr auto width = 50;
    constexpr auto height = 150;

    ol::ConfirmationWindow mWindow{ mGameWindow, 50, 150 };

    const auto size = mWindow.GetWindowSize();

    EXPECT_EQ(size.x, width);
    ASSERT_EQ(size.y, height);
}

TEST_F(ConfirmationWindowTests, IsVisible_FalseByDefault)
{
    ASSERT_FALSE(mWindow.IsVisible());
}

TEST_F(ConfirmationWindowTests, IsVisible_FalseWhenNotShown)
{
    mWindow.Show(false);

    ASSERT_FALSE(mWindow.IsVisible());
}

TEST_F(ConfirmationWindowTests, IsVisible_TrueWhenShown)
{
    mWindow.Show(false);
    mWindow.Show(true);

    ASSERT_TRUE(mWindow.IsVisible());
}

TEST_F(ConfirmationWindowTests, IsConfirmButtonEnabled_TrueByDefault)
{
    ASSERT_TRUE(mWindow.IsConfirmButtonEnabled());
}

TEST_F(ConfirmationWindowTests, IsConfirmButtonEnabled_FalseWhenDisabled)
{
    mWindow.SetConfirmButtonEnabled(false);

    ASSERT_FALSE(mWindow.IsConfirmButtonEnabled());
}

TEST_F(ConfirmationWindowTests, IsConfirmButtonEnabled_TrueWhenEnabled)
{
    mWindow.SetConfirmButtonEnabled(false);
    mWindow.SetConfirmButtonEnabled(true);

    ASSERT_TRUE(mWindow.IsConfirmButtonEnabled());
}

TEST_F(ConfirmationWindowTests, SetConfirmButtonAction_ActionNotComplete)
{
    bool changed = false;
    auto action = [&changed] { changed = true; };

    mWindow.SetConfirmButtonAction(action);

    ASSERT_FALSE(changed);
}

TEST_F(ConfirmationWindowTests, SetConfirmButtonAction_Confirm_ActionComplete)
{
    bool changed = false;
    auto action = [&changed] { changed = true; };

    mWindow.SetConfirmButtonAction(action);
    mWindow.Confirm();

    ASSERT_TRUE(changed);
}

TEST_F(ConfirmationWindowTests, SetDeclineButtonAction_ActionNotComplete)
{
    bool changed = false;
    auto action = [&changed] { changed = true; };

    mWindow.SetDeclineButtonAction(action);

    ASSERT_FALSE(changed);
}

TEST_F(ConfirmationWindowTests, SetDeclineButtonAction_Decline_ActionComplete)
{
    bool changed = false;
    auto action = [&changed] { changed = true; };

    mWindow.SetDeclineButtonAction(action);
    mWindow.Decline();

    ASSERT_TRUE(changed);
}

TEST_F(ConfirmationWindowTests, SetContent_ChangesPosition)
{
    auto content = ol::Group::create();
    auto position_before = content->getPosition();

    mWindow.SetContent(content);

    auto position_after = content->getPosition();

    EXPECT_NE(position_before.x, position_after.x);
    ASSERT_NE(position_before.y, position_after.y);
}

TEST_F(ConfirmationWindowTests, SetContent_ChangesSize)
{
    auto content = ol::Group::create();
    auto size_before = content->getSize();

    mWindow.SetContent(content);

    ASSERT_NE(size_before.y, content->getSize().y);
}

TEST_F(ConfirmationWindowTests,
       GetEnableConfirmButtonCallback_EnablesConfirmButton)
{
    mWindow.SetConfirmButtonEnabled(false);

    auto enable_button = mWindow.GetEnableConfirmButtonCallback();
    enable_button();

    ASSERT_TRUE(mWindow.IsConfirmButtonEnabled());
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
