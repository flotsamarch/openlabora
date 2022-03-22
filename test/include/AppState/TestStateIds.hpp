#ifndef TESTSTATEIDS_HPP_
#define TESTSTATEIDS_HPP_

#include <variant>

namespace Test
{

struct TestState1Id {};
struct TestState2Id {};
struct TestStateFinalId {};

using TestStateIds = std::variant<TestState1Id, TestState2Id, TestStateFinalId>;

} // namespace Test

#endif // TESTSTATEIDS_HPP_
