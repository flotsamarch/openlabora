#include <gtest/gtest.h>

#include "state/StateMachine.hpp"
#include "state/gs/GSTest.hpp"

class StateMachineTest : public ::testing::Test
{
protected:
    StateMachine mStateMachine
        { StateMachine(StateInitializers::TestState{},
                       StateInitializers::FinalState{}) };
};

TEST(StateMachineTests, FinalStateCheckSucceeds)
{
    StateMachine mStateMachine
        { StateMachine(StateInitializers::FinalState{},
                       StateInitializers::FinalState{}) };
    ASSERT_TRUE(mStateMachine.HaveReachedFinalState());
}

TEST_F(StateMachineTest, ValidOnCreation)
{
    ASSERT_FALSE(mStateMachine.HaveReachedFinalState());
}


TEST_F(StateMachineTest, PushStateDoesNotFail)
{
    ASSERT_NO_FATAL_FAILURE(mStateMachine.PushState<StateInitializers::FinalState>());
}

TEST_F(StateMachineTest, NonCompleteStateStays)
{
    ASSERT_NO_FATAL_FAILURE(mStateMachine.AdvanceCompleteState());
    ASSERT_FALSE(mStateMachine.HaveReachedFinalState());
}

TEST_F(StateMachineTest, UpdateStateDoesNotFail)
{
    ASSERT_NO_FATAL_FAILURE(mStateMachine.UpdateState());
}

TEST_F(StateMachineTest, HandleEventDoesNotFail)
{
    ASSERT_NO_FATAL_FAILURE(mStateMachine.HandleEvent(sf::Event{}));
}

TEST_F(StateMachineTest, CompleteStateAndAdvance)
{
    mStateMachine.UpdateState();
    ASSERT_NO_FATAL_FAILURE(mStateMachine.AdvanceCompleteState());
    ASSERT_TRUE(mStateMachine.HaveReachedFinalState());
}

TEST_F(StateMachineTest, CompleteStateAndAdvanceEvt)
{
    mStateMachine.HandleEvent(sf::Event{});
    ASSERT_NO_FATAL_FAILURE(mStateMachine.AdvanceCompleteState());
    ASSERT_TRUE(mStateMachine.HaveReachedFinalState());
}

TEST_F(StateMachineTest, StateFlow)
{
    mStateMachine.PushState<StateInitializers::TestState>();

    for (int i = 0; i < 10; i++) {
        mStateMachine.UpdateState();
        mStateMachine.AdvanceCompleteState();
        mStateMachine.PushState<StateInitializers::TestState>();
    }

    mStateMachine.UpdateState();
    mStateMachine.AdvanceCompleteState();
    mStateMachine.UpdateState();
    mStateMachine.AdvanceCompleteState();

    ASSERT_TRUE(mStateMachine.HaveReachedFinalState());
}
