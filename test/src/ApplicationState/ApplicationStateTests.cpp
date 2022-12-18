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
#include "ApplicationState/ApplicationContext.hpp"
#include "ApplicationState/TestStates.hpp"

namespace test
{

namespace ol = open_labora;
using AppCtx = ol::ApplicationContext;

TEST(ApplicationStateTests, ChangeState)
{
    auto app = AppCtx::Ptr{};
    auto state = ol::ApplicationState{};
    bool has_been_created{ false };

    state.ChangeState<TestCreationState>(app, has_been_created);

    ASSERT_TRUE(has_been_created);
}

TEST(ApplicationStateFreeFunctionsTests, StateUpdate)
{
    auto app = AppCtx::Ptr{};
    auto state = ol::ApplicationState{};
    auto calls_count = 0;
    auto counter = UpdateCallsCounter{ ol::PtrView{ &calls_count } };

    state.ChangeState<TestState>(app, counter);
    stateUpdate(state, 0.f);

    ASSERT_GT(calls_count, 0);
}

TEST(ApplicationStateFreeFunctionsTests, StateHandleInput)
{
    auto app = AppCtx::Ptr{};
    auto state = ol::ApplicationState{};
    auto input = ol::Input{};
    auto calls_count = 0;
    auto counter = HandleInputCallsCounter{ ol::PtrView{ &calls_count } };

    state.ChangeState<TestState>(app, counter);
    stateHandleInput(state, ol::Input::PtrConst{ &input });

    ASSERT_GT(calls_count, 0);
}

TEST(ApplicationStateFreeFunctionsTests, StateGetDrawableObjects)
{
    auto app = AppCtx::Ptr{};
    auto state = ol::ApplicationState{};
    auto calls_count = 0;
    auto counter = GetDrawableCallsCounter{ ol::PtrView{ &calls_count } };

    state.ChangeState<TestState>(app, counter);
    stateGetDrawableObjects(state);

    ASSERT_GT(calls_count, 0);
}

TEST(ApplicationStateFreeFunctionsTests, StateGetFlagIsFinalTrue)
{
    auto app = AppCtx::Ptr{};
    auto state = ol::ApplicationState{};
    bool has_been_created{ false };

    state.ChangeState<TestCreationState>(app, has_been_created);

    ASSERT_TRUE(stateGetFlagIsFinal(state));
}

TEST(ApplicationStateFreeFunctionsTests, StateGetFlagIsFinalFalse)
{
    auto app = AppCtx::Ptr{};
    auto state = ol::ApplicationState{};

    state.ChangeState<TestState>(app);

    ASSERT_FALSE(stateGetFlagIsFinal(state));
}

} // namespace test

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
