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
#include <variant>
#include <optional>
#include "Application.hpp"
#include "RendererDependenciesMocks.hpp"
#include "RendererMock.hpp"
#include "GameWindowMock.hpp"
#include "Resource/ResourceManagerMock.hpp"
#include "ApplicationState/TestStates.hpp"

namespace test
{

using testing::Return;
using testing::Field;
using testing::NiceMock;

namespace ol = open_labora;

using TestWindow = NiceMock<WindowMock>;
using TestGui = NiceMock<GuiMock<TestWindow>>;
using TestGameWindow = NiceMock<GameWindowMock>;
using AppCtx = ol::ApplicationContext;

template<class T, class Y>
using TestRenderer = NiceMock<RendererMock<T, Y>>;

using TestApp = ol::Application<TestGui,
                                TestWindow,
                                TestGameWindow,
                                TestRenderer,
                                NiceMock<ResourceManagerMock>>;

TEST(ApplicationStatesTest, ChangeState_CreatesState)
{
    TestApp app{{}};
    bool has_been_created{ false };
    ol::state::changeState<state::TestCreationState>(AppCtx::Ptr{ &app },
                                                     has_been_created);

    ASSERT_TRUE(has_been_created);
}

TEST(ApplicationStatesTests, IsFinalState_NonFinalState)
{
    TestApp app{{}};
    ol::state::changeState<state::TestState>(AppCtx::Ptr{ &app });

    ASSERT_FALSE(stateGetFlagIsFinal(app.GetState()));
}

TEST(ApplicationStatesTests, IsFinalState_FinalState)
{
    TestApp app{{}};
    ol::state::changeState<state::TestCreationState>(AppCtx::Ptr{ &app });

    ASSERT_TRUE(stateGetFlagIsFinal(app.GetState()));
}

TEST(ApplicationStatesTests, FinalStateStopsApp)
{
    TestApp app{{}};

    auto&& renderer = app.GetRenderer();

    EXPECT_CALL(renderer, IsWindowOpen)
        .WillOnce(Return(true));

    EXPECT_CALL(renderer, Display); // Main loop executes only once

    EXPECT_CALL(renderer, PollEvent)
        .WillOnce(Return(std::nullopt));

    ol::state::changeState<state::TestCreationState>(AppCtx::Ptr{ &app });
    app.run();
}

TEST(ApplicationMainLoopTests, AppStopsIfWindowIsNotOpen)
{
    auto app = TestApp{{}};
    auto&& renderer = app.GetRenderer();

    EXPECT_CALL(renderer, IsWindowOpen())
        .WillOnce(Return(false));

    app.run();
}

TEST(ApplicationMainLoopTests, DisplayAndClearCalledEveryIteration)
{
    auto app = TestApp{{}};
    constexpr auto iterations = 5;
    constexpr auto open_true_calls = iterations;
    constexpr auto poll_event_calls = iterations;
    constexpr auto display_calls = iterations;

    ol::state::changeState<state::TestState>(AppCtx::Ptr{ &app });

    auto&& renderer = app.GetRenderer();

    EXPECT_CALL(renderer, IsWindowOpen())
        .WillOnce(Return(false));

    EXPECT_CALL(renderer, IsWindowOpen())
        .Times(open_true_calls)
        .WillRepeatedly(Return(true))
        .RetiresOnSaturation();

    EXPECT_CALL(renderer, PollEvent())
        .Times(poll_event_calls)
        .WillRepeatedly(Return(std::nullopt));

    EXPECT_CALL(renderer, Display())
        .Times(display_calls);

    EXPECT_CALL(renderer, Clear())
        .Times(display_calls);

    app.run();
}

TEST(ApplicationMainLoopTests, UpdateCalledEveryIteration)
{
    constexpr auto iterations = 5;
    constexpr auto open_true_calls = iterations;
    constexpr auto poll_event_calls = iterations;
    constexpr auto update_calls = iterations;

    auto app = TestApp{{}};
    auto calls_counter = 0;
    auto counter = UpdateCallsCounter{ ol::PtrView{ &calls_counter } };

    ol::state::changeState<state::TestState>(AppCtx::Ptr{ &app }, counter);

    auto&& renderer = app.GetRenderer();

    EXPECT_CALL(renderer, IsWindowOpen())
        .WillOnce(Return(false));

    EXPECT_CALL(renderer, IsWindowOpen())
        .Times(open_true_calls)
        .WillRepeatedly(Return(true))
        .RetiresOnSaturation();

    EXPECT_CALL(renderer, PollEvent())
        .Times(poll_event_calls)
        .WillRepeatedly(Return(std::nullopt));

    app.run();
    ASSERT_EQ(calls_counter, update_calls);
}

TEST(ApplicationMainLoopTests, HandleEventCalledEveryIteration)
{
    constexpr auto iterations = 5;
    constexpr auto poll_event_calls = 2;
    constexpr auto open_true_calls = iterations;
    auto app = TestApp{{}};

    ol::state::changeState<state::TestState>(AppCtx::Ptr{ &app });

    auto&& renderer = app.GetRenderer();

    EXPECT_CALL(renderer, IsWindowOpen)
        .WillOnce(Return(false));

    EXPECT_CALL(renderer, IsWindowOpen)
        .Times(open_true_calls)
        .WillRepeatedly(Return(true))
        .RetiresOnSaturation();

    EXPECT_CALL(renderer, HandleEvent)
        .Times(iterations * poll_event_calls)
        .WillRepeatedly(Return(true));

    for (auto i = 0; i < iterations; ++i) {
        EXPECT_CALL(renderer, PollEvent)
            .WillOnce(Return(std::nullopt))
            .RetiresOnSaturation();

        EXPECT_CALL(renderer, PollEvent)
            .Times(poll_event_calls)
            .WillRepeatedly(Return(sf::Event{}))
            .RetiresOnSaturation();
    }

    app.run();
}

TEST(ApplicationMainLoopTests, HandleInputCalledEveryIteration)
{
    constexpr auto iterations = 5;
    constexpr auto poll_event_calls = 1;
    constexpr auto open_true_calls = iterations;

    auto app = TestApp{{}};
    auto calls_counter = 0;
    auto event = sf::Event{};
    event.type = sf::Event::KeyPressed;

    auto counter = HandleInputCallsCounter{ ol::PtrView{ &calls_counter } };
    ol::state::changeState<state::TestState>(AppCtx::Ptr{ &app }, counter);

    auto&& renderer = app.GetRenderer();

    EXPECT_CALL(renderer, IsWindowOpen)
        .WillOnce(Return(false));

    EXPECT_CALL(renderer, IsWindowOpen)
        .Times(open_true_calls)
        .WillRepeatedly(Return(true))
        .RetiresOnSaturation();

    EXPECT_CALL(renderer, HandleEvent)
        .Times(iterations * poll_event_calls)
        .WillRepeatedly(Return(false));

    for (auto i = 0; i < iterations; ++i) {
        EXPECT_CALL(renderer, PollEvent)
            .WillOnce(Return(std::nullopt))
            .RetiresOnSaturation();

        EXPECT_CALL(renderer, PollEvent)
            .Times(poll_event_calls)
            .WillRepeatedly(Return(event))
            .RetiresOnSaturation();
    }

    app.run();
    ASSERT_EQ(calls_counter, poll_event_calls * iterations);
}

TEST(ApplicationMainLoopTests, HandleInput_GuiBlocksPropagation)
{
    constexpr auto iterations = 5;
    constexpr auto open_true_calls = iterations;
    constexpr auto consumed_events_per_iteration = 1;
    constexpr auto regular_events_per_iteration  = 2;
    constexpr auto expected_calls = iterations * regular_events_per_iteration;

    auto app = TestApp{{}};
    auto calls_counter = 0 ;
    auto event = sf::Event{};
    event.type = sf::Event::KeyPressed;

    auto counter = HandleInputCallsCounter{ ol::PtrView{ &calls_counter } };
    ol::state::changeState<state::TestState>(AppCtx::Ptr{ &app }, counter);

    auto&& renderer = app.GetRenderer();

    auto regular_event = sf::Event{};
    regular_event.type = sf::Event::KeyPressed;
    auto consumed_event = sf::Event{};
    consumed_event.type = sf::Event::MouseButtonPressed;

    const auto regular_evt_match = Field(&sf::Event::type, regular_event.type);
    const auto consumed_evt_match = Field(&sf::Event::type, consumed_event.type);

    EXPECT_CALL(renderer, IsWindowOpen())
        .WillOnce(Return(false));

    EXPECT_CALL(renderer, IsWindowOpen())
        .Times(open_true_calls)
        .WillRepeatedly(Return(true))
        .RetiresOnSaturation();

    EXPECT_CALL(renderer, HandleEvent(regular_evt_match))
        .WillRepeatedly(Return(false));

    EXPECT_CALL(renderer, HandleEvent(consumed_evt_match))
        .WillRepeatedly(Return(true));

    for (auto i = 0; i < iterations; ++i) {
        EXPECT_CALL(renderer, PollEvent())
            .WillOnce(Return(std::nullopt))
            .RetiresOnSaturation();

        EXPECT_CALL(renderer, PollEvent())
            .Times(consumed_events_per_iteration)
            .WillRepeatedly(Return(consumed_event))
            .RetiresOnSaturation();

        EXPECT_CALL(renderer, PollEvent())
            .Times(regular_events_per_iteration)
            .WillRepeatedly(Return(regular_event))
            .RetiresOnSaturation();
    }

    app.run();
    ASSERT_EQ(calls_counter, expected_calls);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
