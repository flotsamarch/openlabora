#ifndef TESTTRANSITIONS_HPP_
#define TESTTRANSITIONS_HPP_

#include <optional>
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "TestStateIds.hpp"
#include "TestAppStateDefs.hpp"

namespace Test
{

/**
 * Callable for std::visit that allows transitions between test-states during
 * testing of application. Additional details are in original Transitions class.
 */
template <class, class>
class TestTransitions final
{
    template <class TAppState>
    TAppState CreateState()
    {
        using ModelT = typename TAppState::ModelType;
        using ControllerT = typename TAppState::ControllerType;
        using ViewT = typename TAppState::ViewType;
        using MVCState = OpenLabora::AppState<ModelT, ViewT, ControllerT>;

        auto model = std::make_shared<ModelT>();
        auto controller = std::make_shared<ControllerT>();
        auto view = std::make_unique<ViewT>();
        return MVCState{ model, std::move(view), controller };
    }

public:
    template <class T, class Y, class Z>
    TestTransitions(T, Y, Z) {};

    using StateOpt = std::optional<TestState>;

    StateOpt operator()(const TestState1Id&) {
        return CreateState<TestState1>();
    };
    StateOpt operator()(const TestState2Id&) {
        return CreateState<TestState2>();
    };
    StateOpt operator()(const TestStateFinalId&) {
        return CreateState<TestStateFinal>();
    };
};

template <class, class>
class NiceTransitions final
{
    template <class TAppState>
    TAppState CreateState()
    {
        using ModelT = typename TAppState::ModelType;
        using ControllerT = typename TAppState::ControllerType;
        using ViewT = typename TAppState::ViewType;
        using MVCState = OpenLabora::AppState<ModelT, ViewT, ControllerT>;

        auto model = std::make_shared<ModelT>();
        auto controller = std::make_shared<ControllerT>();
        auto view = std::make_unique<ViewT>();
        return MVCState{ model, std::move(view), controller };
    }

public:
    template <class T, class Y, class Z>
    NiceTransitions(T, Y, Z) {};

    using StateOpt = std::optional<NiceState>;

    StateOpt operator()(const TestState1Id&) {
        return CreateState<NiceState1>();
    };
    StateOpt operator()(const TestState2Id&) {
        return CreateState<NiceState2>();
    };
    StateOpt operator()(const TestStateFinalId&) {
        return CreateState<NiceStateFinal>();
    };
};

} // namespace Test

#endif // TESTTRANSITIONS_HPP_
