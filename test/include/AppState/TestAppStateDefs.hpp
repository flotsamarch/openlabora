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

#ifndef TESTAPPSTATE_HPP_
#define TESTAPPSTATE_HPP_

#include "AppState/AppState.hpp"
#include "GameState/Model/NoModel.hpp"
#include "GameState/ControllerMocks.hpp"
#include "GameState/ViewMocks.hpp"

namespace test
{

namespace ol = open_labora;

using TestState1 = ol::AppState<ol::NoModel, GVMock1, GCMock1>;
using TestState2 = ol::AppState<ol::NoModel, GVMock2, GCMock2>;
using TestStateFinal = ol::AppState<ol::NoModel, GVMockFinal, GCMockFinal>;

using NiceState1 = ol::AppState<ol::NoModel,
                                ::testing::NiceMock<GVMock1>,
                                ::testing::NiceMock<GCMock1>>;
using NiceState2 = ol::AppState<ol::NoModel,
                                ::testing::NiceMock<GVMock2>,
                                ::testing::NiceMock<GCMock2>>;
using NiceStateFinal = ol::AppState<ol::NoModel,
                                    ::testing::NiceMock<GVMockFinal>,
                                    ::testing::NiceMock<GCMockFinal>>;

using TestState = std::variant<TestState1, TestState2, TestStateFinal>;
using NiceState = std::variant<NiceState1, NiceState2, NiceStateFinal>;

} // namespace test

#endif // TESTAPPSTATE_HPP_
