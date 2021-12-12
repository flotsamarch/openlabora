#include <gtest/gtest.h>

#include "Application.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSFinal.hpp"
#include "state/ui/UISFinal.hpp"
#include "RendererMock.hpp"
#include "TestStates.hpp"
#include "ResourceManagerMock.hpp"
#include <iostream>

namespace Test
{

using ::testing::Return;
using ::testing::ReturnRef;
using ::testing::_;
using ::testing::NiceMock;

class TFAppBasicTests : public ::testing::Test
{
protected:
    Application mApp{ AppStateDefs::FinalState{},
            std::make_unique<NiceMock<RendererMock>>(),
            std::make_unique<NiceMock<ResourceManagerMock>>() };
};

class TFAppStateMachineTests : public ::testing::Test
{
protected:
    Application mApp{ StateMock{},
            std::make_unique<NiceMock<RendererMock>>(),
            std::make_unique<NiceMock<ResourceManagerMock>>() };
    RendererMock* mRenderer;
public:
    TFAppStateMachineTests() :
        mRenderer{ static_cast<RendererMock*>(&mApp.GetRenderer()) } {}
};

TEST_F(TFAppBasicTests, StateGetter)
{
    ASSERT_NE(mApp.GetState().get(), nullptr);
}

TEST_F(TFAppBasicTests, AppClosesNoWindow)
{
    auto renderer = static_cast<RendererMock*>(&mApp.GetRenderer());

    EXPECT_CALL(*renderer, IsWindowOpen())
        .Times(1)
        .WillOnce(Return(false));

    ASSERT_NO_FATAL_FAILURE(mApp.run());
}

TEST_F(TFAppBasicTests, AppClosesInFinalState)
{
    auto renderer = static_cast<RendererMock*>(&mApp.GetRenderer());

    EXPECT_CALL(*renderer, IsWindowOpen())
        .Times(1)
        .WillOnce(Return(true));

    ON_CALL(*renderer, PollEvent(_))
        .WillByDefault(Return(false));

    ASSERT_NO_FATAL_FAILURE(mApp.run());
}

TEST_F(TFAppStateMachineTests, MainLoopUpdatesMemberObjects)
{
    auto game_state = static_cast<GSMock*>(mApp.GetState()->GetGameState());
    auto ui_state = static_cast<UISMock*>(mApp.GetState()->GetUiState());
    // Iterate 10 times then simulate window closure
    // Renderer
    EXPECT_CALL(*mRenderer, IsWindowOpen())
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_CALL(*mRenderer, IsWindowOpen())
        .Times(10)
        .WillRepeatedly(Return(true))
        .RetiresOnSaturation();

    EXPECT_CALL(*mRenderer, Render(_, _, _))
        .Times(10);

    EXPECT_CALL(*mRenderer, PollEvent(_))
        .Times(10)
        .WillRepeatedly(Return(false));

    // Game state
    EXPECT_CALL(*game_state, Update(_))
        .Times(10);

    // Ui state
    EXPECT_CALL(*ui_state, Update(_))
        .Times(10);

    ASSERT_NO_FATAL_FAILURE(mApp.run());
}

TEST_F(TFAppStateMachineTests, EventHandling)
{
    auto game_state = static_cast<GSMock*>(mApp.GetState()->GetGameState());
    auto ui_state = static_cast<UISMock*>(mApp.GetState()->GetUiState());

    // Renderer
    EXPECT_CALL(*mRenderer, IsWindowOpen())
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_CALL(*mRenderer, IsWindowOpen())
        .Times(3)
        .WillRepeatedly(Return(true))
        .RetiresOnSaturation();

    for (int i = 0; i < 3; i++) {
        EXPECT_CALL(*mRenderer, PollEvent(_))
            .Times(1)
            .WillOnce(Return(false))
            .RetiresOnSaturation();

        EXPECT_CALL(*mRenderer, PollEvent(_))
            .Times(10)
            .WillRepeatedly(Return(true))
            .RetiresOnSaturation();
    }

    // Game state
    EXPECT_CALL(*game_state, HandleEvent(_))
        .Times(30);

    // Ui state
    EXPECT_CALL(*ui_state, HandleEvent(_))
        .Times(30);

    ASSERT_NO_FATAL_FAILURE(mApp.run());
}

TEST(StateMachineTests, IsSameStateTest)
{
    Application app{ StateMock{},
            std::make_unique<NiceMock<RendererMock>>(),
            std::make_unique<NiceMock<ResourceManagerMock>>() };
    Application app2{  StateTest{},
            std::make_unique<NiceMock<RendererMock>>(),
            std::make_unique<NiceMock<ResourceManagerMock>>() };
    Application app3{ AppStateDefs::FinalState{},
            std::make_unique<NiceMock<RendererMock>>(),
            std::make_unique<NiceMock<ResourceManagerMock>>() };

    ASSERT_TRUE(app.GetState()->IsSameState<StateMock>());
    ASSERT_TRUE(app2.GetState()->IsSameState<StateTest>());
    ASSERT_TRUE(app3.GetState()->IsSameState<AppStateDefs::FinalState>());
}

TEST(StateMachineTests, ChangeStateTest)
{
    Application app{ StateTest{},
            std::make_unique<NiceMock<RendererMock>>(),
            std::make_unique<NiceMock<ResourceManagerMock>>() };

    auto renderer = static_cast<RendererMock*>(&app.GetRenderer());
    NiceMock<DesktopMock> desktop;

    EXPECT_CALL(*renderer, GetDesktop())
        .WillRepeatedly(ReturnRef(desktop));
    EXPECT_CALL(desktop, RemoveWidgets(_, _))
        .Times(1);

    app.GetState()->ChangeState<AppStateDefs::FinalState>();

    ASSERT_FALSE(app.GetState()->IsSameState<StateTest>());
    ASSERT_TRUE(app.GetState()->IsSameState<AppStateDefs::FinalState>());
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
