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
#include <algorithm>
#include "Misc/EnumMap.hpp"

namespace test
{

namespace ol = open_labora;

enum class TestEnum
{
    Begin, Test1 = Begin, Test2, Test3, End
};

static constexpr size_t kItemCount =
    static_cast<size_t>(TestEnum::End) - static_cast<size_t>(TestEnum::Begin);

TEST(EnumMapTests, GetSize_DefaultConstructor)
{
    auto map = ol::EnumMap<TestEnum, int>{};

    ASSERT_EQ(kItemCount, map.GetSize());
}

TEST(EnumMapTests, GetSize_InitializerListConstructor)
{
    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, 1 },
        { TestEnum::Test2, 2 },
        { TestEnum::Test3, 3 }
    };

    ASSERT_EQ(kItemCount, map.GetSize());
}

TEST(EnumMapTests, Get)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map.Get(TestEnum::Test1), value_1);
    EXPECT_EQ(map.Get(TestEnum::Test2), value_2);
    ASSERT_EQ(map.Get(TestEnum::Test3), value_3);
}

TEST(EnumMapTests, Get_DefaultConstructor)
{
    auto map = ol::EnumMap<TestEnum, int>{};

    EXPECT_EQ(map.Get(TestEnum::Test1), 0);
    EXPECT_EQ(map.Get(TestEnum::Test2), 0);
    ASSERT_EQ(map.Get(TestEnum::Test3), 0);
}

TEST(EnumMapTests, Get_Mutate)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>{};
    map.Get(TestEnum::Test1) = value_1;
    map.Get(TestEnum::Test2) = value_2;
    map.Get(TestEnum::Test3) = value_3;

    EXPECT_EQ(map.Get(TestEnum::Test1), value_1);
    EXPECT_EQ(map.Get(TestEnum::Test2), value_2);
    ASSERT_EQ(map.Get(TestEnum::Test3), value_3);
}

TEST(EnumMapTests, At)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map.At(TestEnum::Test1), value_1);
    EXPECT_EQ(map.At(TestEnum::Test2), value_2);
    ASSERT_EQ(map.At(TestEnum::Test3), value_3);
}

TEST(EnumMapTests, At_DefaultConstructor)
{
    auto map = ol::EnumMap<TestEnum, int>{};

    EXPECT_EQ(map.At(TestEnum::Test1), 0);
    EXPECT_EQ(map.At(TestEnum::Test2), 0);
    ASSERT_EQ(map.At(TestEnum::Test3), 0);
}

TEST(EnumMapTests, At_Mutate)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>{};
    map.At(TestEnum::Test1) = value_1;
    map.At(TestEnum::Test2) = value_2;
    map.At(TestEnum::Test3) = value_3;

    EXPECT_EQ(map.Get(TestEnum::Test1), value_1);
    EXPECT_EQ(map.Get(TestEnum::Test2), value_2);
    ASSERT_EQ(map.Get(TestEnum::Test3), value_3);
}

TEST(EnumMapTests, At_BoundsChecking_LowerBound)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>{};
    map.Get(TestEnum::Test1) = value_1;
    map.Get(TestEnum::Test2) = value_2;
    map.Get(TestEnum::Test3) = value_3;

    ASSERT_THROW(map.At(static_cast<TestEnum>(-1)), std::out_of_range);
}

TEST(EnumMapTests, At_BoundsChecking_UpperBound)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>{};
    map.Get(TestEnum::Test1) = value_1;
    map.Get(TestEnum::Test2) = value_2;
    map.Get(TestEnum::Test3) = value_3;

    const auto size = map.GetSize();
    ASSERT_THROW(map.At(static_cast<TestEnum>(size)), std::out_of_range);
}

TEST(EnumMapTests, OperatorSquareBrackets_DefaultConstructor)
{
    auto map = ol::EnumMap<TestEnum, int>{};

    EXPECT_EQ(map[TestEnum::Test1], 0);
    EXPECT_EQ(map[TestEnum::Test2], 0);
    ASSERT_EQ(map[TestEnum::Test3], 0);
}

TEST(EnumMapTests, OperatorSquareBrackets_Read)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map[TestEnum::Test1], value_1);
    EXPECT_EQ(map[TestEnum::Test2], value_2);
    ASSERT_EQ(map[TestEnum::Test3], value_3);
}

TEST(EnumMapTests, OperatorSquareBrackets_Mutate)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>{};
    map[TestEnum::Test1] = value_1;
    map[TestEnum::Test2] = value_2;
    map[TestEnum::Test3] = value_3;

    EXPECT_EQ(map[TestEnum::Test1], value_1);
    EXPECT_EQ(map[TestEnum::Test2], value_2);
    ASSERT_EQ(map[TestEnum::Test3], value_3);
}

TEST(EnumMapIteratorTests, Begin_NotEqualsEnd)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };

    auto begin = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };
    auto end = ol::EnumMapIterator<MapT>{ TestEnum::End, container.end() };

    ASSERT_NE(begin, end);
}

TEST(EnumMapConstIteratorTests, Begin_NotEqualsEnd)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    static constexpr auto container = std::array{ 1, 2, 3 };

    constexpr auto cont_begin = container.begin();
    constexpr auto cont_end = container.end();
    auto begin = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, cont_begin };
    auto end = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, cont_end };

    ASSERT_NE(begin, end);
}

TEST(EnumMapIteratorTests, ArrowOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ expected_key, container.begin() };

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapConstIteratorTests, ArrowOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    constexpr auto begin = container.begin();
    constexpr auto it = ol::EnumMapConstIterator<MapT>{ expected_key, begin };

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapIteratorTests, ArrowOperator_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };

    ASSERT_EQ(it->second, container.front());
}

TEST(EnumMapConstIteratorTests, ArrowOperator_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    constexpr auto begin = container.begin();
    constexpr auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, begin };

    ASSERT_EQ(it->second, container.front());
}

TEST(EnumMapIteratorTests, StarOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ expected_key, container.begin() };

    ASSERT_EQ((*it).first, expected_key);
}

TEST(EnumMapConstIteratorTests, StarOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    constexpr auto begin = container.begin();
    constexpr auto it = ol::EnumMapConstIterator<MapT>{ expected_key, begin };

    ASSERT_EQ((*it).first, expected_key);
}

TEST(EnumMapIteratorTests, StarOperator_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };

    ASSERT_EQ((*it).second, container.front());
}

TEST(EnumMapConstIteratorTests, StarOperator_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    constexpr auto begin = container.begin();
    constexpr auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, begin };

    ASSERT_EQ((*it).second, container.front());
}

TEST(EnumMapIteratorTests, PreincrementOperator_KeyIsSecondInEnum)
{
    constexpr auto expected_key = TestEnum::Begin + 1;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };

    ++it;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapConstIteratorTests, PreincrementOperator_KeyIsSecondInEnum)
{
    constexpr auto expected_key = TestEnum::Begin + 1;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    constexpr auto begin = container.begin();
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, begin };

    ++it;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapIteratorTests, PreincrementOperator_ValueEqualsSecondContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };

    ++it;

    ASSERT_EQ(it->second, container[1]);
}

TEST(EnumMapConstIteratorTests,
     PreincrementOperator_ValueEqualsSecondContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    constexpr auto begin = container.begin();
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, begin };

    ++it;

    ASSERT_EQ(it->second, container[1]);
}

TEST(EnumMapIteratorTests, PostincrementOperator_KeyIsSecondInEnum)
{
    constexpr auto expected_key = TestEnum::Begin + 1;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };

    it++;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapConstIteratorTests, PostincrementOperator_KeyIsSecondInEnum)
{
    constexpr auto expected_key = TestEnum::Begin + 1;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    constexpr auto begin = container.begin();
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, begin };

    it++;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapIteratorTests, PostincrementOperator_ValueEqualsSecondContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };

    it++;

    ASSERT_EQ(it->second, container[1]);
}

TEST(EnumMapConstIteratorTests,
     PostincrementOperator_ValueEqaulsSecondContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    constexpr auto begin = container.begin();
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, begin };

    it++;

    ASSERT_EQ(it->second, container[1]);
}

TEST(EnumMapIteratorTests, PostincrementOperator_ReturnValue_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ expected_key, container.begin() };

    auto old = it++;

    ASSERT_EQ(old->first, expected_key);
}

TEST(EnumMapConstIteratorTests, PostincrementOperator_ReturnValue_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    constexpr auto begin = container.begin();
    auto it = ol::EnumMapConstIterator<MapT>{ expected_key, begin };

    auto old = it++;

    ASSERT_EQ(old->first, expected_key);
}

TEST(EnumMapIteratorTests,
     PostincrementOperator_ReturnValue_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin, container.begin() };

    auto old = it++;

    ASSERT_EQ(old->second, container[0]);
}

TEST(EnumMapConstIteratorTests,
     PostincrementOperator_ReturnValue_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    constexpr auto begin = container.begin();
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin, begin };

    auto old = it++;

    ASSERT_EQ(old->second, container[0]);
}

TEST(EnumMapIteratorTests, PredecrementOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin + 1, next };

    --it;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapConstIteratorTests, PredecrementOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    auto next = std::next(container.begin());
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin + 1, next };

    --it;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapIteratorTests, PredecrementOperator_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin + 1, next };

    --it;

    ASSERT_EQ(it->second, container[0]);
}

TEST(EnumMapConstIteratorTests,
     PredecrementOperator_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin + 1, next };

    --it;

    ASSERT_EQ(it->second, container[0]);
}

TEST(EnumMapIteratorTests, PostdecrementOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin + 1, next };

    it--;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapConstIteratorTests, PostdecrementOperator_KeyIsEnumBegin)
{
    constexpr auto expected_key = TestEnum::Begin;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    auto next = std::next(container.begin());
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin + 1, next };

    it--;

    ASSERT_EQ(it->first, expected_key);
}

TEST(EnumMapIteratorTests, PostdecrementOperator_ValueEqualsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin + 1, next };

    it--;

    ASSERT_EQ(it->second, container[0]);
}

TEST(EnumMapConstIteratorTests,
     PostdecrementOperator_ValueEqaulsFirstContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin + 1, next };

    it--;

    ASSERT_EQ(it->second, container[0]);
}

TEST(EnumMapIteratorTests, PostdecrementOperator_ReturnValue_KeyIsSecondInEnum)
{
    constexpr auto expected_key = TestEnum::Begin + 1;

    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapIterator<MapT>{ expected_key, next };

    auto old = it--;

    ASSERT_EQ(old->first, expected_key);
}

TEST(EnumMapConstIteratorTests,
     PostdecrementOperator_ReturnValue_KeyIsSecondInEnum)
{
    constexpr auto expected_key = TestEnum::Begin + 1;
    static constexpr auto container = std::array{ 1, 2, 3 };

    using MapT = ol::EnumMap<TestEnum, int>;
    auto next = std::next(container.begin());
    auto it = ol::EnumMapConstIterator<MapT>{ expected_key, next };

    auto old = it--;

    ASSERT_EQ(old->first, expected_key);
}

TEST(EnumMapIteratorTests,
     PostdecrementOperator_ReturnValue_ValueEqualsSecondContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;
    auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapIterator<MapT>{ TestEnum::Begin + 1, next };

    auto old = it--;

    ASSERT_EQ(old->second, container[1]);
}

TEST(EnumMapConstIteratorTests,
     PostdecrementOperator_ReturnValue_ValueEqualsSecondContainerItem)
{
    using MapT = ol::EnumMap<TestEnum, int>;

    static constexpr auto container = std::array{ 1, 2, 3 };
    auto next = std::next(container.begin());
    auto it = ol::EnumMapConstIterator<MapT>{ TestEnum::Begin + 1, next };

    auto old = it--;

    ASSERT_EQ(old->second, container[1]);
}

TEST(EnumMapTests, Begin_KeyIsEnumBegin)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;
    constexpr auto expected_key = TestEnum::Begin;

    auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    ASSERT_EQ(map.Begin()->first, expected_key);
}

TEST(EnumMapTests, Begin_ValueIsValue1)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    ASSERT_EQ(map.Begin()->second, value_1);
}

TEST(EnumMapTests, CBegin_KeyIsEnumBegin)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;
    constexpr auto expected_key = TestEnum::Begin;

    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    ASSERT_EQ(map.CBegin()->first, expected_key);
}

TEST(EnumMapTests, CBegin_ValueIsValue1)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    ASSERT_EQ(map.CBegin()->second, value_1);
}

TEST(EnumMapTests, Begin_Const_KeyIsEnumBegin)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;
    constexpr auto expected_key = TestEnum::Begin;

    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    ASSERT_EQ(map.Begin()->first, expected_key);
}

TEST(EnumMapTests, Begin_Const_ValueIsValue1)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    ASSERT_EQ(map.Begin()->second, value_1);
}

TEST(EnumMapTests, End_ReturnsEndIterator)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    auto it = map.Begin();
    std::advance(it, map.GetSize());

    ASSERT_EQ(it, map.End());
}

TEST(EnumMapTests, CEnd_ReturnsConstEndIterator)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    auto it = map.CBegin();
    std::advance(it, map.GetSize());

    ASSERT_EQ(it, map.CEnd());
}

TEST(EnumMapTests, End_Const_ReturnsConstEndIterator)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    static constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    auto it = map.Begin();
    std::advance(it, map.GetSize());

    ASSERT_EQ(it, map.End());
}

TEST(EnumMapIteratorTests, RangeBasedForLoop)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = ol::EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map.Get(TestEnum::Test1), value_1);
    EXPECT_EQ(map.Get(TestEnum::Test2), value_2);
    ASSERT_EQ(map.Get(TestEnum::Test3), value_3);
}

TEST(EnumMapIteratorTests, RangeBasedForLoop_Mutate)
{
    auto map = ol::EnumMap<TestEnum, int>{};

    for (auto&& [key, value] : map) {
        value++;
    }

    for (auto&& [_, value] : map) {
        ASSERT_GT(value, 0);
    }
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
