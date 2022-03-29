#ifndef TESTAPPSTATE_HPP_
#define TESTAPPSTATE_HPP_

#include "AppState/AppState.hpp"
#include "GameState/NoModel.hpp"
#include "GameState/ControllerMocks.hpp"
#include "GameState/ViewMocks.hpp"

namespace Test
{

using TestState1 = OpenLabora::AppState<OpenLabora::NoModel, GVMock1, GCMock1>;
using TestState2 = OpenLabora::AppState<OpenLabora::NoModel, GVMock2, GCMock2>;
using TestStateFinal = OpenLabora::AppState<OpenLabora::NoModel,
                                            GVMockFinal, GCMockFinal>;

using NiceState1 = OpenLabora::AppState<OpenLabora::NoModel,
                                        ::testing::NiceMock<GVMock1>,
                                        ::testing::NiceMock<GCMock1>>;
using NiceState2 = OpenLabora::AppState<OpenLabora::NoModel,
                                        ::testing::NiceMock<GVMock2>,
                                        ::testing::NiceMock<GCMock2>>;
using NiceStateFinal = OpenLabora::AppState<OpenLabora::NoModel,
                                            ::testing::NiceMock<GVMockFinal>,
                                            ::testing::NiceMock<GCMockFinal>>;

using TestState = std::variant<TestState1, TestState2, TestStateFinal>;
using NiceState = std::variant<NiceState1, NiceState2, NiceStateFinal>;

} // namespace Test

#endif // TESTAPPSTATE_HPP_
