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
template <class TGui, class TWindow, class TStateIdsVariant>
class TestTransitions final
{
    template <class TAppState>
    TAppState CreateState()
    {
        using std::make_shared;
        using ModelT = typename TAppState::ModelT;
        using ControllerT = typename TAppState::ControllerT;
        using ViewT = typename TAppState::ViewT;
        using MVCState = OpenLabora::AppState<ModelT, ViewT, ControllerT>;

        auto model = make_shared<ModelT>();
        auto controller = make_shared<ControllerT>();
        auto view = std::make_unique<ViewT>();
        return MVCState{ model, std::move(view), controller };
    }

    using StateOpt = std::optional<TestState>;

    StateOpt operator()(const TestState1Id&) {
        CreateState<TestState1>();
    };
    StateOpt operator()(const TestState2Id&) {
        CreateState<TestState2>();
    };
    StateOpt operator()(const TestStateFinalId&) {
        CreateState<TestStateFinal>();
    };
};

} // namespace Test

#endif // TESTTRANSITIONS_HPP_
