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
#include "RendererMock.hpp"
#include "RendererDependenciesMocks.hpp"
#include "AppState/TestTransitions.hpp"
#include "AppState/TestStateIds.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace test
{

struct Empty{};
using ::testing::Return;
using ::testing::Field;

template<template<class...> class TTransitions,
         class TStateVariant, class TStateVariantId>
using TestApp = open_labora::Application<Empty, Empty,
                                        RendererMock,
                                        TTransitions,
                                        TStateVariant,
                                        TStateVariantId,
                                        IResourceManagerMock>;

/**
 * Create a state transitions class that returns only a single default state
 * in every case. This is used to initialize Application class in tests in some
 * specific default state.
 *
 * @tparam TRequiredState - Default state
 */
template <class TRequiredState>
class TransitionToDefault
{
    template<class, class>
    struct TtdImpl final
    {
        template <class T, class Y, class Z>
        TtdImpl(T, Y, Z) {};

        template <class T>
        std::optional<std::variant<TRequiredState>> operator()(const T&)
        {
            using ModelT = typename TRequiredState::ModelType;
            using ControllerT = typename TRequiredState::ControllerType;
            using ViewT = typename TRequiredState::ViewType;
            using MVCState = open_labora::AppState<ModelT, ViewT, ControllerT>;

            auto model = std::make_shared<ModelT>();
            auto controller = std::make_shared<ControllerT>();
            auto view = std::make_unique<ViewT>();
            return MVCState{ model, std::move(view), controller };
        };
    };

public:
    template<class T, class Y>
    using Impl = TtdImpl<T, Y>;
};

template<class T, class Y>
using Ttd1 = TransitionToDefault<TestState1>::Impl<T, Y>;
template<class T, class Y>
using Ttd2 = TransitionToDefault<TestState2>::Impl<T, Y>;
template<class T, class Y>
using TtdFinal = TransitionToDefault<TestStateFinal>::Impl<T, Y>;

using State1 = std::variant<TestState1>;
using State1Id = std::variant<TestState1Id>;

TEST(ApplicationStatesTests, IsSameState_OnlyState)
{
    TestApp<Ttd1, State1, State1Id> app_in_state_1{{}};

    ASSERT_TRUE(app_in_state_1.IsSameState<TestState1>());
}

TEST(ApplicationStatesTests, IsSameState_StateSuite)
{
    TestApp<TestTransitions, TestState, TestStateIds> app_all_states{{}};

    EXPECT_TRUE(app_all_states.IsSameState<TestState1>());
    EXPECT_FALSE(app_all_states.IsSameState<TestState2>());
    ASSERT_FALSE(app_all_states.IsSameState<TestStateFinal>());
}

TEST(ApplicationStatesTests, IsFinalState_OnlyState)
{
    TestApp<Ttd1, State1, State1Id> app_in_state_1{{}};

    ASSERT_TRUE(app_in_state_1.IsFinalState());
}

TEST(ApplicationStatesTests, IsFinalState_StateSuite)
{
    TestApp<TestTransitions, TestState, TestStateIds> app_all_states{{}};

    ASSERT_FALSE(app_all_states.IsFinalState());
}

TEST(ApplicationStatesTests, ChangeState_NonFinal)
{
    TestApp<TestTransitions, TestState, TestStateIds> app{{}};

    app.ChangeState(TestState2Id{});

    EXPECT_TRUE(app.IsSameState<TestState2>());
    EXPECT_FALSE(app.IsFinalState());
}

TEST(ApplicationStatesTests, ChangeState_ToFinal)
{
    TestApp<TestTransitions, TestState, TestStateIds> app{{}};

    app.ChangeState(TestStateFinalId{});

    EXPECT_TRUE(app.IsFinalState());
    ASSERT_TRUE(app.IsSameState<TestStateFinal>());
}

TEST(ApplicationTests, MainLoop)
{
    constexpr auto cycles{ 5u };
    constexpr auto display_calls{ cycles };
    constexpr auto update_calls{ cycles };
    constexpr auto poll_event_calls{ cycles };
    constexpr auto open_true_calls{ cycles };

    TestApp<NiceTransitions,
            NiceState,
            TestStateIds> app{{}};

    auto&& renderer = app.GetRenderer();
    auto&& state = app.GetState();

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

    auto setup_expects = [] (auto&& state)
    {
        EXPECT_CALL(*state.view, Update)
            .Times(update_calls);

        EXPECT_CALL(*state.controller, Update)
            .Times(update_calls);
    };
    std::visit(setup_expects, state);

    ASSERT_NO_FATAL_FAILURE(app.run());
}

TEST(ApplicationStatesTests, FinalStateStopsApp)
{
    TestApp<NiceTransitions,
            NiceState,
            TestStateIds> app{{}};

    auto&& renderer = app.GetRenderer();

    ON_CALL(renderer, IsWindowOpen)
        .WillByDefault(Return(true));

    EXPECT_CALL(renderer, Display()) // Main loop executes only once
        .Times(1);

    app.ChangeState(TestStateFinalId{});
    ASSERT_NO_FATAL_FAILURE(app.run());
}

TEST(ApplicationStatesTests, ChangeStateRemovesWidgets)
{
    TestApp<NiceTransitions,
            NiceState,
            TestStateIds> app{{}};

    auto&& renderer = app.GetRenderer();

    EXPECT_CALL(renderer, RemoveAllWidgets())
        .Times(2);

    EXPECT_NO_FATAL_FAILURE(app.ChangeState(TestState2Id{}));
    ASSERT_NO_FATAL_FAILURE(app.ChangeState(TestStateFinalId{}));
}

TEST(ApplicationEventHandlingTests, HandleEvents_Basic)
{
    TestApp<TestTransitions,
            TestState,
            TestStateIds> app{{}};

    constexpr auto poll_event_calls{ 5u };

    auto&& renderer = app.GetRenderer();
    auto&& state = app.GetState();

    auto event{ std::optional<sf::Event>{ sf::Event{} } };
    event->type = sf::Event::MouseMoved;

    const auto evt_type_match = Field(&sf::Event::type, event->type);

    EXPECT_CALL(renderer, HandleEvent(evt_type_match))
        .WillRepeatedly(Return(false));

    EXPECT_CALL(renderer, PollEvent())
        .WillOnce(Return(std::nullopt));

    EXPECT_CALL(renderer, PollEvent())
        .Times(poll_event_calls)
        .WillRepeatedly(Return(event))
        .RetiresOnSaturation();

    auto setup_expects = [&evt_type_match] (auto&& state)
    {
        EXPECT_CALL(*state.view, HandleEvent(evt_type_match))
            .Times(poll_event_calls);

        EXPECT_CALL(*state.controller, HandleEvent(evt_type_match))
            .Times(poll_event_calls);
    };
    std::visit(setup_expects, state);

    ASSERT_NO_FATAL_FAILURE(app.HandleEvents());
}

TEST(ApplicationEventHandlingTests, HandleEvents_GuiConsumes)
{
    TestApp<TestTransitions,
            TestState,
            TestStateIds> app{{}};

    constexpr auto poll_event_pack_size{ 3u };
    constexpr auto handle_event_calls{ 10u };

    auto&& renderer = app.GetRenderer();
    auto&& state = app.GetState();

    auto consumed_event{ std::optional<sf::Event>{ sf::Event{} } };
    auto regular_event{ std::optional<sf::Event>{ sf::Event{} } };

    consumed_event->type = sf::Event::MouseButtonPressed;

    const auto regular_evt_match = Field(&sf::Event::type, regular_event->type);
    const auto consumed_evt_match = Field(&sf::Event::type,
                                          consumed_event->type);

    EXPECT_CALL(renderer, HandleEvent(regular_evt_match))
        .WillRepeatedly(Return(false));

    EXPECT_CALL(renderer, HandleEvent(consumed_evt_match))
        .WillRepeatedly(Return(true));

    EXPECT_CALL(renderer, PollEvent())
        .WillOnce(Return(std::nullopt));

    for (size_t i{ 0u }; i < 5u; ++i) {
        EXPECT_CALL(renderer, PollEvent())
            .Times(poll_event_pack_size)
            .WillOnce(Return(consumed_event))
            .WillOnce(Return(regular_event))
            .WillOnce(Return(regular_event))
            .RetiresOnSaturation();
    }

    auto setup_expects = [&regular_evt_match] (auto&& state)
    {
        EXPECT_CALL(*state.view, HandleEvent(regular_evt_match))
            .Times(handle_event_calls);

        EXPECT_CALL(*state.controller, HandleEvent(regular_evt_match))
            .Times(handle_event_calls);
    };
    std::visit(setup_expects, state);

    ASSERT_NO_FATAL_FAILURE(app.HandleEvents());
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
