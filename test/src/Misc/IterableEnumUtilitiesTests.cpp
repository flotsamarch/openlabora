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
#include "Misc/IterableEnumUtilities.hpp"

namespace test
{

namespace ol = open_labora;

enum class TestEnum
{
    One, Begin = One, Two, Three, End
};

constexpr auto kBegin = static_cast<int>(TestEnum::Begin);
constexpr auto kEnd = static_cast<int>(TestEnum::End);
constexpr auto kRange = kEnd - kBegin;

TEST(IterableEnumOperatorsTests, OperatorPreincrement_Once)
{
    auto type = TestEnum::One;

    ++type;

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::Two);
}

TEST(IterableEnumOperatorsTests, OperatorPreincrement_Loop)
{
    auto type = TestEnum::One;

    for (auto i = 0; i < kRange; ++i) {
        ++type;
    }

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::End);
}

TEST(IterableEnumOperatorsTests, OperatorPredecrement_Once)
{
    auto type = TestEnum::Two;

    --type;

    EXPECT_NE(type, TestEnum::Two);
    ASSERT_EQ(type, TestEnum::One);
}

TEST(IterableEnumOperatorsTests, OperatorPredecrement_Loop)
{
    auto type = TestEnum::End;

    for (auto i = 0; i < kRange; ++i) {
        --type;
    }

    EXPECT_NE(type, TestEnum::End);
    ASSERT_EQ(type, TestEnum::One);
}

TEST(IterableEnumOperatorsTests, OperatorPostincrement_Once)
{
    auto type = TestEnum::One;

    type++;

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::Two);
}

TEST(IterableEnumOperatorsTests, OperatorPostincrement_Once_ReturnValue)
{
    constexpr auto expected_value = TestEnum::One;
    auto type = expected_value;

    auto old = type++;

    ASSERT_EQ(old, expected_value);
}

TEST(IterableEnumOperatorsTests, OperatorPostincrement_Loop)
{
    auto type = TestEnum::One;

    for (auto i = 0; i < kRange; ++i) {
        type++;
    }

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::End);
}

TEST(IterableEnumOperatorsTests, OperatorPostdecrement_Once)
{
    auto type = TestEnum::Two;

    type--;

    EXPECT_NE(type, TestEnum::Two);
    ASSERT_EQ(type, TestEnum::One);
}

TEST(IterableEnumOperatorsTests, OperatorPostdecrement_Once_ReturnValue)
{
    constexpr auto expected_value = TestEnum::Two;
    auto type = expected_value;

    auto old = type--;

    ASSERT_EQ(old, expected_value);
}

TEST(IterableEnumOperatorsTests, OperatorPostdecrement_Loop)
{
    auto type = TestEnum::End;

    for (auto i = 0; i < kRange; ++i) {
        type--;
    }

    EXPECT_NE(type, TestEnum::End);
    ASSERT_EQ(type, TestEnum::One);
}

TEST(IterableEnumOperatorsTests, OperatorPlusLeft_PlusOne)
{
    auto type = TestEnum::One;

    type = type + 1;

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::Two);
}

TEST(IterableEnumOperatorsTests, OperatorPlusLeft_PlusRange)
{
    auto type = TestEnum::One;

    type = type + kRange;

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::End);
}

TEST(IterableEnumOperatorsTests, OperatorPlusRight_PlusOne)
{
    auto type = TestEnum::One;

    type = 1 + type;

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::Two);
}

TEST(IterableEnumOperatorsTests, OperatorPlusRight_PlusRange)
{
    auto type = TestEnum::One;

    type = kRange + type;

    EXPECT_NE(type, TestEnum::One);
    ASSERT_EQ(type, TestEnum::End);
}

TEST(IterableEnumOperatorsTests, OperatorMinusLeft_MinusOne)
{
    auto type = TestEnum::Two;

    type = type - 1;

    EXPECT_NE(type, TestEnum::Two);
    ASSERT_EQ(type, TestEnum::One);
}

TEST(IterableEnumOperatorsTests, OperatorMinusLeft_MinusRange)
{
    auto type = TestEnum::End;

    type = type - kRange;

    EXPECT_NE(type, TestEnum::End);
    ASSERT_EQ(type, TestEnum::One);
}

TEST(EnumIteratorTests, DereferenceOperatorReturnsValue)
{
    for (auto value = TestEnum::Begin; value != TestEnum::End; ++value) {
        auto iterator = ol::EnumRange<TestEnum>::EnumIterator{ value };

        ASSERT_EQ(*iterator, value);
    }
}

TEST(EnumIteratorTests, IncrementOperatorOnce)
{
    auto iterator = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    ++iterator;

    ASSERT_NE(*iterator, TestEnum::One);
    ASSERT_EQ(*iterator, TestEnum::Two);
}

TEST(EnumIteratorTests, IncrementOperatorLoop)
{
    auto iterator = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    for (auto i = 0; i < kRange; ++i) {
        ++iterator;
    }

    EXPECT_NE(*iterator, TestEnum::One);
    ASSERT_EQ(*iterator, TestEnum::End);
}

TEST(EnumIteratorTests, EqualityOperator_Equals)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_TRUE(iterator_1 == iterator_2);
}

TEST(EnumIteratorTests, EqualityOperator_NotEqual)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };

    ASSERT_FALSE(iterator_1 == iterator_2);
}

TEST(EnumIteratorTests, InequalityOperator_NotEqual)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };

    ASSERT_TRUE(iterator_1 != iterator_2);
}

TEST(EnumIteratorTests, InequalityOperator_Equals)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_FALSE(iterator_1 != iterator_2);
}

TEST(EnumIteratorTests, OperatorLess_Less)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };

    ASSERT_TRUE(iterator_1 < iterator_2);
}

TEST(EnumIteratorTests, OperatorLess_Equals)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_FALSE(iterator_1 < iterator_2);
}

TEST(EnumIteratorTests, OperatorLess_More)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_FALSE(iterator_1 < iterator_2);
}

TEST(EnumIteratorTests, OperatorLessEqual_Less)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };

    ASSERT_TRUE(iterator_1 <= iterator_2);
}

TEST(EnumIteratorTests, OperatorLessEqual_Equals)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_TRUE(iterator_1 <= iterator_2);
}

TEST(EnumIteratorTests, OperatorLessEqual_More)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_FALSE(iterator_1 <= iterator_2);
}

TEST(EnumIteratorTests, OperatorMore_Less)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };

    ASSERT_FALSE(iterator_1 > iterator_2);
}

TEST(EnumIteratorTests, OperatorMore_Equals)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_FALSE(iterator_1 > iterator_2);
}

TEST(EnumIteratorTests, OperatorMore_More)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_TRUE(iterator_1 > iterator_2);
}

TEST(EnumIteratorTests, OperatorMoreEqual_Less)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };

    ASSERT_FALSE(iterator_1 >= iterator_2);
}

TEST(EnumIteratorTests, OperatorMoreEqual_Equals)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_TRUE(iterator_1 >= iterator_2);
}

TEST(EnumIteratorTests, OperatorMoreEqual_More)
{
    auto iterator_1 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::Two };
    auto iterator_2 = ol::EnumRange<TestEnum>::EnumIterator{ TestEnum::One };

    ASSERT_TRUE(iterator_1 >= iterator_2);
}

TEST(EnumRangeTests, Begin_IsEnumBegin)
{
    auto range = ol::EnumRange<TestEnum>{};

    ASSERT_EQ(*range.begin(), TestEnum::Begin);
}

TEST(EnumRangeTests, End_IsEnumEnd)
{
    auto range = ol::EnumRange<TestEnum>{};

    ASSERT_EQ(*range.end(), TestEnum::End);
}

TEST(EnumRangeTests, CBegin_IsEnumBegin)
{
    auto range = ol::EnumRange<TestEnum>{};

    ASSERT_EQ(*range.cbegin(), TestEnum::Begin);
}

TEST(EnumRangeTests, CEnd_IsEnumEnd)
{
    auto range = ol::EnumRange<TestEnum>{};

    ASSERT_EQ(*range.cend(), TestEnum::End);
}

TEST(EnumRangeTests, RangeBasedForLoop)
{
    auto iterations_count = 0;

    for ([[maybe_unused]]auto item : ol::EnumRange<TestEnum>{}) {
        ++iterations_count;
        ASSERT_LE(iterations_count, kRange);
    }
    ASSERT_GT(iterations_count, 0);
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
