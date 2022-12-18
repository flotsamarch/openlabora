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
#include "Misc/TupleUtils.hpp"

namespace test
{

namespace ol = open_labora;

using ol::tuple_utils::createTuple;
using ol::tuple_utils::applyUntilFalse;

TEST(TupleUtilsTests, CreateTuple_SizeOne)
{
    const auto ref_tuple = std::tuple<int>{};
    const auto tuple = createTuple<int, 1>(0);
    ASSERT_EQ(ref_tuple, tuple);
}

TEST(TupleUtilsTests, CreateTuple_SizeOneInitialized)
{
    constexpr auto init_value = 5;
    auto ref_tuple = std::tuple<int>{};
    std::get<0>(ref_tuple) = init_value;
    const auto tuple = createTuple<int, 1>(init_value);
    ASSERT_EQ(ref_tuple, tuple);
}

TEST(TupleUtilsTests, CreateTuple_SizeTwo)
{
    const auto ref_tuple = std::tuple<int, int>{};
    const auto tuple = createTuple<int, 2>(0);
    ASSERT_EQ(ref_tuple, tuple);
}

TEST(TupleUtilsTests, CreateTuple_SizeTwoInitialized)
{
    constexpr auto init_value = 5;
    auto ref_tuple = std::tuple<int, int>{};
    std::get<0>(ref_tuple) = init_value;
    std::get<1>(ref_tuple) = init_value;
    const auto tuple = createTuple<int, 2>(init_value);
    ASSERT_EQ(ref_tuple, tuple);
}

TEST(TupleUtilsTests, CreateTuple_SizeFive)
{
    const auto ref_tuple = std::tuple<int, int, int, int, int>{};
    const auto tuple = createTuple<int, 5>(0);
    ASSERT_EQ(ref_tuple, tuple);
}

TEST(TupleUtilsTests, ApplyUntilFalse_AppliedOnce_FirstTrue)
{
    constexpr auto init_value = 'a';
    auto call_counter = 0;
    std::tuple<char> tuple{};
    std::get<0>(tuple) = init_value;
    auto pred_is_a = [] (auto value) { return value == 'a'; };
    auto mutator = [&call_counter] (auto) { ++call_counter; };

    applyUntilFalse(tuple, mutator, pred_is_a);
    ASSERT_EQ(call_counter, 1);
}

TEST(TupleUtilsTests, ApplyUntilFalse_AppliedOnce_FirstFalse)
{
    constexpr auto init_value = 'b';
    auto call_counter = 0;
    std::tuple<char> tuple{};
    std::get<0>(tuple) = init_value;
    auto pred_is_a = [] (auto value) { return value == 'a'; };
    auto mutator = [&call_counter] (auto) { ++call_counter; };

    applyUntilFalse(tuple, mutator, pred_is_a);
    ASSERT_EQ(call_counter, 1);
}

TEST(TupleUtilsTests, ApplyUntilFalse_AlwaysTrue)
{
    constexpr auto tuple_size = 3;
    constexpr auto init_value = 'a';
    auto call_counter = 0;
    auto tuple = createTuple<char, tuple_size>(init_value);
    auto pred_is_a = [] (auto value) { return value == 'a'; };
    auto mutator = [&call_counter] (auto) { ++call_counter; };

    applyUntilFalse(tuple, mutator, pred_is_a);
    ASSERT_EQ(call_counter, tuple_size);
}

TEST(TupleUtilsTests, ApplyUntilFalse_AppliedPartially)
{
    constexpr auto tuple_size = 4;
    constexpr auto init_value = 'a';
    auto call_counter = 0;
    auto tuple = createTuple<char, tuple_size>(init_value);
    auto pred_is_a = [] (auto value) { return value == 'a'; };
    auto mutator = [&call_counter] (auto) { ++call_counter; };

    std::get<tuple_size - 2>(tuple) = 'b';
    applyUntilFalse(tuple, mutator, pred_is_a);
    ASSERT_EQ(call_counter, tuple_size - 1);
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
