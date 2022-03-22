#ifndef TESTAPPSTATE_HPP_
#define TESTAPPSTATE_HPP_

#include "AppState/AppState.hpp"
#include "GameState/Model.hpp"
#include "GameState/ControllerMocks.hpp"
#include "GameState/ViewMocks.hpp"

namespace Test
{

using TestState1 = OpenLabora::AppState<OpenLabora::NoModel, GCMock1, GVMock1>;
using TestState2 = OpenLabora::AppState<OpenLabora::NoModel, GCMock2, GVMock2>;
using TestStateFinal = OpenLabora::AppState<OpenLabora::NoModel,
                                            GCMockFinal, GVMockFinal>;

using TestState = std::variant<TestState1, TestState2, TestStateFinal>;

} // namespace Test

#endif // TESTAPPSTATE_HPP_
