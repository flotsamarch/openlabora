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

namespace Test
{

using OpenLabora::EnumMap;

enum class TestEnum
{
    Begin, Test1 = Begin, Test2, Test3, End
};

static constexpr size_t kItemCount =
    static_cast<size_t>(TestEnum::End) - static_cast<size_t>(TestEnum::Begin);

TEST(EnumMapTests, GetSize_DefaultCtor)
{
    auto map = EnumMap<TestEnum, int>{};

    ASSERT_EQ(kItemCount, map.GetSize());
}

TEST(EnumMapTests, GetSize_InitializerListCtor)
{
    auto map = EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, 1 },
        { TestEnum::Test2, 2 },
        { TestEnum::Test3, 3 }
    };

    ASSERT_EQ(kItemCount, map.GetSize());
}

TEST(EnumMapTests, GetSize_InitializerListCtorConstexpr)
{
    constexpr auto map = EnumMap<TestEnum, bool>
    {
        { TestEnum::Test1, true },
        { TestEnum::Test2, false },
        { TestEnum::Test3, true }
    };

    ASSERT_EQ(kItemCount, map.GetSize());
}

TEST(EnumMapTests, Get)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map.Get(TestEnum::Test1), value_1);
    EXPECT_EQ(map.Get(TestEnum::Test2), value_2);
    ASSERT_EQ(map.Get(TestEnum::Test3), value_3);
}

TEST(EnumMapTests, Get_Constexpr)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map.Get(TestEnum::Test1), value_1);
    EXPECT_EQ(map.Get(TestEnum::Test2), value_2);
    ASSERT_EQ(map.Get(TestEnum::Test3), value_3);
}

TEST(EnumMapTests, Get_Default)
{
    auto map = EnumMap<TestEnum, int>{};

    EXPECT_EQ(map.Get(TestEnum::Test1), 0);
    EXPECT_EQ(map.Get(TestEnum::Test2), 0);
    ASSERT_EQ(map.Get(TestEnum::Test3), 0);
}

TEST(EnumMapTests, Get_Mutator)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = EnumMap<TestEnum, int>{};
    map.Get(TestEnum::Test1) = value_1;
    map.Get(TestEnum::Test2) = value_2;
    map.Get(TestEnum::Test3) = value_3;

    EXPECT_EQ(map.Get(TestEnum::Test1), value_1);
    EXPECT_EQ(map.Get(TestEnum::Test2), value_2);
    ASSERT_EQ(map.Get(TestEnum::Test3), value_3);
}

TEST(EnumMapTests, OperatorSquareBrackets_Default)
{
    auto map = EnumMap<TestEnum, int>{};

    EXPECT_EQ(map[TestEnum::Test1], 0);
    EXPECT_EQ(map[TestEnum::Test2], 0);
    ASSERT_EQ(map[TestEnum::Test3], 0);
}

TEST(EnumMapTests, OperatorSquareBrackets_Read)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map[TestEnum::Test1], value_1);
    EXPECT_EQ(map[TestEnum::Test2], value_2);
    ASSERT_EQ(map[TestEnum::Test3], value_3);
}

TEST(EnumMapTests, OperatorSquareBrackets_ReadConstexpr)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    EXPECT_EQ(map[TestEnum::Test1], value_1);
    EXPECT_EQ(map[TestEnum::Test2], value_2);
    ASSERT_EQ(map[TestEnum::Test3], value_3);
}

TEST(EnumMapTests, OperatorSquareBrackets_Mutator)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    auto map = EnumMap<TestEnum, int>{};
    map[TestEnum::Test1] = value_1;
    map[TestEnum::Test2] = value_2;
    map[TestEnum::Test3] = value_3;

    EXPECT_EQ(map[TestEnum::Test1], value_1);
    EXPECT_EQ(map[TestEnum::Test2], value_2);
    ASSERT_EQ(map[TestEnum::Test3], value_3);
}

TEST(EnumMapIteratorTests, RangeBasedForLoop_Regular)
{
    auto map = EnumMap<TestEnum, int>{};

    for (auto&& [key, value] : map) {
        value++;
    }

    auto greater_than_zero = [] (auto&& item) { return item.second > 0; };
    bool all_incremented =
        std::all_of(map.begin(), map.end(), greater_than_zero);
    ASSERT_TRUE(all_incremented);
}

TEST(EnumMapIteratorTests, RangeBasedForLoop_Const)
{
    constexpr auto value_1 = 1;
    constexpr auto value_2 = 2;
    constexpr auto value_3 = 3;

    constexpr auto map = EnumMap<TestEnum, int>
    {
        { TestEnum::Test1, value_1 },
        { TestEnum::Test2, value_2 },
        { TestEnum::Test3, value_3 }
    };

    for (auto i{ 1 }; auto&& [key, value] : map) {
        EXPECT_EQ(value, i++);
    }
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
