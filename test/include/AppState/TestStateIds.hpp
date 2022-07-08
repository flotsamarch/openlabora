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

#ifndef TESTSTATEIDS_HPP_
#define TESTSTATEIDS_HPP_

#include <variant>

namespace test
{

struct TestState1Id {};
struct TestState2Id {};
struct TestStateFinalId {};

using TestStateIds = std::variant<TestState1Id, TestState2Id, TestStateFinalId>;

} // namespace test

#endif // TESTSTATEIDS_HPP_
