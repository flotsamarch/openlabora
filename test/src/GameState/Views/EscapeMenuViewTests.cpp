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
#include "GameState/ModelMock.hpp"
#include "GameState/Views/EscapeMenuView.hpp"
#include "GameState/ViewModels/EscapeMenuViewModel.hpp"
#include "GameWindowMock.hpp"
#include "Input/Input.hpp"

namespace test
{

namespace ol = open_labora;

using testing::_;
using testing::NiceMock;

using TestModel = NiceMock<ModelMock>;
using TestEscapeMenuViewModel = ol::EscapeMenuViewModel<TestModel>;
using TestEscapeMenuView = ol::EscapeMenuView<TestEscapeMenuViewModel>;
using TestWindow = NiceMock<GameWindowMock>;

namespace
{

tgui::GuiSFML _gui; // Required to create GUI objects

} // namespace anonymous

class EscapeMenuViewTests : public testing::Test
{
protected:
    using WinPtr = ol::IGameWindow::Ptr;

    TestModel mModel{};
    TestEscapeMenuViewModel mViewModel{ ol::PtrView{ &mModel } };
    ol::ApplicationContext::Ptr mApp{};
    std::shared_ptr<TestWindow> mWindow = std::make_shared<TestWindow>();
    ol::Input mInput{};
};

TEST(EscapeMenuViewModelTests, ClosedByDefault)
{
    auto model = TestModel{};
    auto view_model = TestEscapeMenuViewModel{ ol::PtrView{ &model } };

    ASSERT_FALSE(view_model.IsOpen());
}

TEST(EscapeMenuViewModelTests, SetOpen)
{
    auto model = TestModel{};
    auto view_model = TestEscapeMenuViewModel{ ol::PtrView{ &model } };
    view_model.SetLockCameraMovementCallback([]{});
    view_model.SetUnlockCameraMovementCallback([]{});

    view_model.SetOpen(true);

    ASSERT_TRUE(view_model.IsOpen());
}

TEST(EscapeMenuViewModelTests, SetClosed)
{
    auto model = TestModel{};
    auto view_model = TestEscapeMenuViewModel{ ol::PtrView{ &model } };
    view_model.SetLockCameraMovementCallback([]{});
    view_model.SetUnlockCameraMovementCallback([]{});

    view_model.SetOpen(true);
    view_model.SetOpen(false);

    ASSERT_FALSE(view_model.IsOpen());
}

TEST(EscapeMenuViewModelTests, SetOpen_LocksCamera)
{
    bool locked = false;
    auto model = TestModel{};
    auto view_model = TestEscapeMenuViewModel{ ol::PtrView{ &model } };
    view_model.SetLockCameraMovementCallback([&locked] { locked = true; });
    view_model.SetUnlockCameraMovementCallback([]{});

    view_model.SetOpen(true);

    ASSERT_TRUE(locked);
}

TEST(EscapeMenuViewModelTests, SetClosed_UnlocksCamera)
{
    bool unlocked = false;
    auto model = TestModel{};
    auto view_model = TestEscapeMenuViewModel{ ol::PtrView{ &model } };
    view_model.SetLockCameraMovementCallback([]{});
    view_model.SetUnlockCameraMovementCallback([&unlocked] { unlocked = true; });

    view_model.SetOpen(true);
    view_model.SetOpen(false);

    ASSERT_TRUE(unlocked);
}

TEST_F(EscapeMenuViewTests, ConstructorAddsWidgets)
{
    EXPECT_CALL(*mWindow, AddWidget(_));

    TestEscapeMenuView mView{ mApp, mWindow, ol::PtrView{ &mViewModel } };
}

TEST_F(EscapeMenuViewTests, HandleInput_NoInput)
{
    auto lock_counter = 0;
    auto unlock_counter = 0;
    TestEscapeMenuView mView{ mApp, mWindow, ol::PtrView{ &mViewModel } };

    mViewModel.SetLockCameraMovementCallback([&lc = lock_counter] { ++lc; });
    mViewModel.SetUnlockCameraMovementCallback([&uc = unlock_counter] { ++uc; });

    sf::Event event;
    event.type = sf::Event::MouseMoved;

    mInput.HandleEvent(event);

    bool was_input_consumed = mView.HandleInput(ol::Input::PtrConst{ &mInput });

    EXPECT_FALSE(was_input_consumed);
    EXPECT_EQ(lock_counter, 0);
    ASSERT_EQ(unlock_counter, 0);
}

TEST_F(EscapeMenuViewTests, HandleInput_SingleEscapeLocksCamera)
{
    auto lock_counter = 0;
    TestEscapeMenuView mView{ mApp, mWindow, ol::PtrView{ &mViewModel } };

    mViewModel.SetLockCameraMovementCallback([&lc = lock_counter] { ++lc; });

    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Escape;

    mInput.HandleEvent(event);

    bool was_input_consumed = mView.HandleInput(ol::Input::PtrConst{ &mInput });

    EXPECT_TRUE(was_input_consumed);
    ASSERT_EQ(lock_counter, 1);
}

TEST_F(EscapeMenuViewTests, HandleInput_DoubleEscapeUnlocksCamera)
{
    auto lock_counter = 0;
    auto unlock_counter = 0;
    bool was_input_consumed = false;
    TestEscapeMenuView mView{ mApp, mWindow, ol::PtrView{ &mViewModel } };

    mViewModel.SetLockCameraMovementCallback([&lc = lock_counter] { ++lc; });
    mViewModel.SetUnlockCameraMovementCallback([&uc = unlock_counter] { ++uc; });

    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Escape;

    mInput.HandleEvent(event); // Simulate Escape press

    event.type = sf::Event::KeyReleased;
    mInput.HandleEvent(event); // Simulate Escape release

    event.type = sf::Event::KeyPressed;
    mInput.HandleEvent(event); // Simulate Escape press again

    while (mInput.HasUnhandledInput()) {
        auto result = mView.HandleInput(ol::Input::PtrConst{ &mInput });
        mInput.Advance();
        if (result) {
            was_input_consumed = true;
        }
    }

    EXPECT_TRUE(was_input_consumed);
    EXPECT_EQ(lock_counter, 1);
    ASSERT_EQ(unlock_counter, 1);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
