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

#ifndef TESTSTATES_HPP_
#define TESTSTATES_HPP_

#include "ApplicationState/ApplicationContext.hpp"
#include "Input/Input.hpp"

namespace test
{

namespace ol = open_labora;

// State that raises a flag when constructed
struct TestCreationState final
{
    TestCreationState(ol::ApplicationContext::Ptr) {}

    TestCreationState(ol::ApplicationContext::Ptr, bool& has_been_created)
    { has_been_created = true; };
};

struct UpdateCallsCounter
{
    ol::PtrView<int> counter;

    int& operator*()
    {
        return *counter;
    }
};

struct HandleInputCallsCounter
{
    ol::PtrView<int> counter;

    int& operator*()
    {
        return *counter;
    }
};

struct GetDrawableCallsCounter
{
    ol::PtrView<int> counter;

    int& operator*()
    {
        return *counter;
    }
};

inline void stateUpdate(TestCreationState& state, float) {}

inline bool stateHandleInput(TestCreationState& state, ol::Input::PtrConst)
{ return false; }

inline ol::DrawableRangeConst
stateGetDrawableObjects(TestCreationState&)
{ return {}; }

inline bool stateGetFlagIsFinal(const TestCreationState&) noexcept
{ return true; }

/**
 * State that increments bound counter when a corresponding free function
 * is called
 */
struct TestState final
{
    UpdateCallsCounter update_calls_counter;
    HandleInputCallsCounter handle_input_calls_counter;
    GetDrawableCallsCounter get_drawable_calls_counter;

    TestState(ol::ApplicationContext::Ptr) {}

    TestState(ol::ApplicationContext::Ptr,
              UpdateCallsCounter _update_calls_counter,
              HandleInputCallsCounter _handle_input_calls_counter,
              GetDrawableCallsCounter _get_drawable_calls_counter)
        : update_calls_counter{ _update_calls_counter },
          handle_input_calls_counter{ _handle_input_calls_counter },
          get_drawable_calls_counter{ _get_drawable_calls_counter } {}

    TestState(ol::ApplicationContext::Ptr,
              UpdateCallsCounter _update_calls_counter)
        : update_calls_counter{ _update_calls_counter } {}

    TestState(ol::ApplicationContext::Ptr,
              HandleInputCallsCounter _handle_input_calls_counter)
        : handle_input_calls_counter{ _handle_input_calls_counter } {}

    TestState(ol::ApplicationContext::Ptr,
              GetDrawableCallsCounter _get_drawable_calls_counter)
        : get_drawable_calls_counter{ _get_drawable_calls_counter } {}
};

inline void stateUpdate(TestState& state, float)
{
    auto&& counter = state.update_calls_counter;
    if(counter.counter != nullptr) {
        ++(*counter);
    }
}

inline bool stateHandleInput(TestState& state, ol::Input::PtrConst)
{
    auto&& counter = state.handle_input_calls_counter;
    return counter.counter != nullptr && (*counter)++ > 0;
}

inline ol::DrawableRangeConst stateGetDrawableObjects(TestState& state)
{
    auto&& counter = state.get_drawable_calls_counter;
    if (counter.counter != nullptr) {
        ++(*counter);
    }
    return {};
}

inline bool stateGetFlagIsFinal(const TestState&) noexcept
{ return false; }

namespace state
{

struct TestCreationState{};
struct TestState{};

inline void changeState(state::TestCreationState,
                        ol::ApplicationContext::Ptr app,
                        bool& created)
{ app->ChangeState<test::TestCreationState>(created); }

inline void changeState(state::TestCreationState,
                        ol::ApplicationContext::Ptr app)
{ app->ChangeState<test::TestCreationState>(); }

inline void changeState(state::TestState,
                        ol::ApplicationContext::Ptr app,
                        UpdateCallsCounter update_calls_counter,
                        HandleInputCallsCounter handle_input_calls_counter,
                        GetDrawableCallsCounter get_drawable_calls_counter)
{
    app->ChangeState<test::TestState>(update_calls_counter,
                                      handle_input_calls_counter,
                                      get_drawable_calls_counter);
}

inline void changeState(state::TestState,
                        ol::ApplicationContext::Ptr app)
{
    app->ChangeState<test::TestState>();
}

inline void changeState(state::TestState,
                        ol::ApplicationContext::Ptr app,
                        UpdateCallsCounter update_calls_counter)
{
    app->ChangeState<test::TestState>(update_calls_counter);
}

inline void changeState(state::TestState,
                        ol::ApplicationContext::Ptr app,
                        HandleInputCallsCounter handle_input_calls_counter)
{
    app->ChangeState<test::TestState>(handle_input_calls_counter);
}

inline void changeState(state::TestState,
                        ol::ApplicationContext::Ptr app,
                        GetDrawableCallsCounter get_drawable_calls_counter)
{
    app->ChangeState<test::TestState>(get_drawable_calls_counter);
}

} // namespace state

} // namespace test

#endif // TESTSTATES_HPP_
