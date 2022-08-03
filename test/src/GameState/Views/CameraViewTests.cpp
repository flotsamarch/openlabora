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
#include "GameState/ModelMock.hpp"
#include "GameState/Views/CameraView.hpp"
#include "GameState/ViewModels/CameraViewModel.hpp"
#include "GameWindowMock.hpp"
#include "Input/Input.hpp"

namespace test
{

namespace ol = open_labora;

using testing::NiceMock;
using testing::ReturnRef;

using TestModel = NiceMock<ModelMock>;
using TestWindow = NiceMock<GameWindowMock>;
using TestCameraViewModel = ol::CameraViewModel<TestModel>;
using TestCameraView = ol::CameraView<TestCameraViewModel>;

class CameraViewTests : public testing::Test
{
protected:
    using WinPtr = ol::IGameWindow::Ptr;

    TestModel mModel{};
    TestCameraViewModel mViewModel{ ol::PtrView{ &mModel } };
    ol::ApplicationContext::Ptr mApp{};
    std::shared_ptr<TestWindow> mWindow = std::make_shared<TestWindow>();
    ol::Input mInput{};
};

TEST(CameraViewModelTests, CameraMovementAllowedByDefault)
{
    auto model = TestModel{};
    TestCameraViewModel view_model{ ol::PtrView{ &model } };

    ASSERT_TRUE(view_model.IsCameraMovementAllowed());
}

TEST(CameraViewModelTests, LockCameraMovement)
{
    auto model = TestModel{};
    TestCameraViewModel view_model{ ol::PtrView{ &model } };

    view_model.LockCameraMovement();

    ASSERT_FALSE(view_model.IsCameraMovementAllowed());
}

TEST(CameraViewModelTests, UnlockCameraMovement)
{
    auto model = TestModel{};
    TestCameraViewModel view_model{ ol::PtrView{ &model } };

    view_model.LockCameraMovement();
    view_model.UnlockCameraMovement();

    ASSERT_TRUE(view_model.IsCameraMovementAllowed());
}

TEST(CameraViewModelTests, MultipleLockers)
{
    constexpr auto lockers_count{ 3u };
    auto model = TestModel{};
    TestCameraViewModel view_model{ ol::PtrView{ &model } };

    for(auto i{ 0u }; i < lockers_count; ++i) {
        view_model.LockCameraMovement();
    }
    view_model.UnlockCameraMovement();

    ASSERT_FALSE(view_model.IsCameraMovementAllowed());
}

TEST(CameraViewModelTests, MultipleLockersUnlock)
{
    constexpr auto lockers_count{ 3u };
    auto model = TestModel{};
    TestCameraViewModel view_model{ ol::PtrView{ &model } };

    for(auto i{ 0u }; i < lockers_count; ++i) {
        view_model.LockCameraMovement();
    }
    for(auto i{ 0u }; i < lockers_count; ++i) {
        view_model.UnlockCameraMovement();
    }

    ASSERT_TRUE(view_model.IsCameraMovementAllowed());
}

TEST(CameraViewModelTests, LessUsualLockingPattern)
{
    constexpr auto lockers_count{ 7u };
    auto model = TestModel{};
    TestCameraViewModel view_model{ ol::PtrView{ &model } };

    for(auto i{ 0u }; i < lockers_count; ++i) {
        view_model.LockCameraMovement();
        view_model.LockCameraMovement();
        view_model.UnlockCameraMovement();
    }
    for(auto i{ 0u }; i < lockers_count; ++i) {
        view_model.UnlockCameraMovement();
        view_model.LockCameraMovement();
        view_model.UnlockCameraMovement();
    }

    ASSERT_TRUE(view_model.IsCameraMovementAllowed());
}

TEST_F(CameraViewTests, ConstructorDoesCameraPosition)
{
    EXPECT_CALL(*mWindow, SetView);

    TestCameraView mView{ mApp, mWindow, ol::PtrView{ &mViewModel } };
}

TEST_F(CameraViewTests, HandleInput_NoMouseMovement)
{
    TestCameraView mView{ mApp, mWindow, ol::PtrView{ &mViewModel } };
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Key::Unknown;

    mInput.HandleEvent(event);

    EXPECT_CALL(*mWindow, GetView)
        .Times(0);

    EXPECT_CALL(*mWindow, SetView)
        .Times(0);

    mView.HandleInput(ol::Input::PtrConst{ &mInput });
}

TEST_F(CameraViewTests, HandleInput_MouseMovesCamera)
{
    constexpr auto move_event_count{ 5u };
    TestCameraView mView{ mApp, mWindow, ol::PtrView{ &mViewModel } };
    auto view = sf::View{};
    auto event = sf::Event{};
    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Right;
    mInput.HandleEvent(event);

    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = 1.f;
    event.mouseMove.y = 1.f;

    for(auto i{ 0u }; i < move_event_count; ++i) {
        mInput.HandleEvent(event);
    }

    EXPECT_CALL(*mWindow, GetView)
        .Times(move_event_count)
        .WillRepeatedly(ReturnRef(view));

    EXPECT_CALL(*mWindow, SetView)
        .Times(move_event_count);

    while(mInput.HasUnhandledInput()) {
        mView.HandleInput(ol::Input::PtrConst{ &mInput });
        mInput.Advance();
    }
}

} // namespace test

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
