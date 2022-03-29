#include <gtest/gtest.h>
#include <variant>
#include <optional>
#include "Application.hpp"
#include "RendererDependenciesMocks.hpp"
#include "AppState/TestTransitions.hpp"
#include "AppState/TestStateIds.hpp"
#include "AppState/TestAppStateDefs.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace Test
{

using ::testing::NiceMock;

using NiceWindow = NiceMock<WindowMock<false>>;
using NiceGui = NiceMock<GuiMock<NiceWindow, false>>;

template<template<class...> class TTransitions,
         class TStateVariant, class TStateVariantId>
using TestApp = OpenLabora::Application<NiceGui,
                                        NiceWindow,
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
            using MVCState = OpenLabora::AppState<ModelT, ViewT, ControllerT>;

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

TEST(ApplicationStatesTests, IsSameStateBasic)
{
    using State1 = std::variant<TestState1>;
    using State2 = std::variant<TestState2>;
    using StateFinal = std::variant<TestStateFinal>;

    using State1Id = std::variant<TestState1Id>;
    using State2Id = std::variant<TestState2Id>;
    using StateFinalId = std::variant<TestStateFinalId>;

    TestApp<Ttd1, State1, State1Id> app_in_state_1;
    TestApp<Ttd2, State2, State2Id> app_in_state_2;
    TestApp<TtdFinal, StateFinal, StateFinalId> app_in_state_final;
    TestApp<TestTransitions, TestState, TestStateIds> app_all_states;

    EXPECT_TRUE(app_in_state_1.IsSameState<TestState1>());
    EXPECT_TRUE(app_in_state_1.IsFinalState());
    EXPECT_TRUE(app_in_state_2.IsSameState<TestState2>());
    EXPECT_TRUE(app_in_state_2.IsFinalState());
    EXPECT_TRUE(app_in_state_final.IsSameState<TestStateFinal>());
    EXPECT_TRUE(app_in_state_final.IsFinalState());
    EXPECT_TRUE(app_all_states.IsSameState<TestState1>());
    EXPECT_FALSE(app_all_states.IsFinalState());
    EXPECT_FALSE(app_all_states.IsSameState<TestState2>());
    ASSERT_FALSE(app_all_states.IsSameState<TestStateFinal>());
}

TEST(ApplicationStatesTests, ChangeState)
{
    TestApp<TestTransitions, TestState, TestStateIds> app;
    EXPECT_TRUE(app.IsSameState<TestState1>());
    EXPECT_FALSE(app.IsFinalState());

    app.ChangeState(TestState2Id{});
    EXPECT_TRUE(app.IsSameState<TestState2>());
    EXPECT_FALSE(app.IsFinalState());

    app.ChangeState(TestStateFinalId{});
    EXPECT_TRUE(app.IsFinalState());
    ASSERT_TRUE(app.IsSameState<TestStateFinal>());
}

TEST(ApplicationStatesTests, MainLoop)
{
    const auto cycles{ 5u };
    const auto display_calls{ cycles };
    const auto poll_event_calls{ cycles };
    const auto poll_event_true_calls{ 0u };
    const auto open_true_calls{ cycles * 2 };
    const auto open_calls{ open_true_calls + 1 };
    const auto draw_calls{ 0u };
    const auto getSize_calls{ 0u };
    const auto remove_widget_calls{ 0u };
    const auto handle_event_false_calls{ poll_event_true_calls };
    const auto handle_event_true_calls{ 0u };

    using WindowMockConf = WindowMock<true,
                                      true,
                                      open_calls,
                                      open_true_calls,
                                      true,
                                      poll_event_calls,
                                      poll_event_true_calls,
                                      display_calls,
                                      draw_calls,
                                      getSize_calls>;

    using GuiMockConf = GuiMock<WindowMockConf,
                                true,
                                display_calls,
                                remove_widget_calls,
                                handle_event_false_calls,
                                handle_event_true_calls>;


    OpenLabora::Application<GuiMockConf,
                            WindowMockConf,
                            NiceTransitions,
                            NiceState,
                            TestStateIds,
                            IResourceManagerMock> app{};

    ASSERT_NO_FATAL_FAILURE(app.run());
}

TEST(ApplicationStatesTests, FinalStateStopsApp)
{
    const auto display_calls{ 1u };
    const auto poll_event_calls{ 1u };
    const auto poll_event_true_calls{ 0u };
    const auto open_true_calls{ 2u };
    const auto open_calls{ 2u };
    const auto draw_calls{ 0u };
    const auto getSize_calls{ 0u };
    const auto remove_widget_calls{ 1u };
    const auto handle_event_false_calls{ 0u };
    const auto handle_event_true_calls{ 0u };

    using WindowMockConf = WindowMock<true,
                                      true,
                                      open_calls,
                                      open_true_calls,
                                      true,
                                      poll_event_calls,
                                      poll_event_true_calls,
                                      display_calls,
                                      draw_calls,
                                      getSize_calls>;

    using GuiMockConf = GuiMock<WindowMockConf,
                                true,
                                display_calls,
                                remove_widget_calls,
                                handle_event_false_calls,
                                handle_event_true_calls>;


    OpenLabora::Application<GuiMockConf,
                            WindowMockConf,
                            NiceTransitions,
                            NiceState,
                            TestStateIds,
                            IResourceManagerMock> app{};

    app.ChangeState(TestStateFinalId{});
    ASSERT_NO_FATAL_FAILURE(app.run());
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
