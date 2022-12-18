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
#include "Misc/PtrView.hpp"

namespace test
{

namespace ol = open_labora;

struct TestStruct
{
    int value{ 0 };
};

TEST(PtrViewTests, GetNullptr)
{
    ol::PtrView<int> ptr{ nullptr };
    ol::PtrView<const int> ptr_c{ nullptr };
    ol::PtrView<double> ptr_d{ nullptr };
    ol::PtrView<TestStruct> ptr_s{ nullptr };

    EXPECT_EQ(ptr_s.Get(), nullptr);
    EXPECT_EQ(ptr_d.Get(), nullptr);
    EXPECT_EQ(ptr_c.Get(), nullptr);
    ASSERT_EQ(ptr.Get(), nullptr);
}

TEST(PtrViewTests, DefaultIsNullptr)
{
    ol::PtrView<int> ptr{};
    ol::PtrView<const int> ptr_c{};
    ol::PtrView<double> ptr_d{ nullptr };
    ol::PtrView<TestStruct> ptr_s{ nullptr };

    EXPECT_EQ(ptr_s.Get(), nullptr);
    EXPECT_EQ(ptr_d.Get(), nullptr);
    EXPECT_EQ(ptr_c.Get(), nullptr);
    ASSERT_EQ(ptr.Get(), nullptr);
}

TEST(PtrViewTests, Get)
{
    auto value{ 5 };
    const auto cvalue{ 5 };
    auto dvalue{ 5.0 };
    auto obj{ TestStruct{} };

    ol::PtrView ptr{ &value };
    ol::PtrView ptr_c{ &cvalue };
    ol::PtrView ptr_d{ &dvalue };
    ol::PtrView ptr_obj{ &obj };

    EXPECT_NE(ptr.Get(), nullptr);
    EXPECT_NE(ptr_c.Get(), nullptr);
    EXPECT_NE(ptr_d.Get(), nullptr);
    EXPECT_NE(ptr_obj.Get(), nullptr);

    EXPECT_EQ(*ptr.Get(), value);
    EXPECT_EQ(*ptr_c.Get(), cvalue);
    EXPECT_EQ(*ptr_d.Get(), dvalue);
    EXPECT_EQ((*ptr_obj.Get()).value, obj.value);

    EXPECT_EQ(ptr.Get(), &value);
    EXPECT_EQ(ptr_c.Get(), &cvalue);
    EXPECT_EQ(ptr_d.Get(), &dvalue);
    ASSERT_EQ(ptr_obj.Get(), &obj);
}

TEST(PtrViewOperatorTests, OperatorBool)
{
    auto value{ 5 };
    ol::PtrView ptr{ &value };
    ol::PtrView<int> ptr_null{};

    EXPECT_FALSE(ptr_null);
    EXPECT_TRUE(ptr);
}

TEST(PtrViewOperatorTests, OperatorStar)
{
    auto value{ 5 };
    const auto cvalue{ 5 };
    auto dvalue{ 5.0 };
    auto obj{ TestStruct{} };

    ol::PtrView ptr{ &value };
    ol::PtrView ptr_c{ &cvalue };
    ol::PtrView ptr_d{ &dvalue };
    ol::PtrView ptr_obj{ &obj };

    EXPECT_EQ(*ptr, value);
    EXPECT_EQ(*ptr_c, cvalue);
    EXPECT_EQ(*ptr_d, dvalue);
    ASSERT_EQ((*ptr_obj).value, obj.value);
}

TEST(PtrViewOperatorTests, ArrowOperator)
{
    constexpr auto value{ 5 };
    auto obj{ TestStruct{ value } };
    ol::PtrView ptr_obj{ &obj };

    ASSERT_EQ(ptr_obj->value, value);
}

TEST(PtrViewTests, Reset)
{
    auto value_init{ 5 };
    auto value_after{ 10 };

    ol::PtrView ptr_1{ &value_init };
    ol::PtrView ptr_2{ &value_init };
    ol::PtrView ptr_3{ &value_init };

    ptr_1.Reset(&value_after);
    ptr_2.Reset(nullptr);
    ptr_3.Reset();

    EXPECT_EQ(ptr_3.Get(), nullptr);
    EXPECT_EQ(ptr_2.Get(), nullptr);
    EXPECT_NE(ptr_1.Get(), nullptr);
    ASSERT_EQ(ptr_1.Get(), &value_after);
}

TEST(PtrViewTests, Swap)
{
    auto value_1{ 5 };
    auto value_2{ 10 };

    ol::PtrView ptr_1{ &value_1 };
    ol::PtrView ptr_2{ &value_2 };

    ptr_1.Swap(ptr_2);

    EXPECT_EQ(ptr_2.Get(), &value_1);
    ASSERT_EQ(ptr_1.Get(), &value_2);
}

TEST(PtrViewTests, Release)
{
    auto value{ 5 };

    ol::PtrView ptr{ &value };

    auto ptr_r = ptr.Release();

    EXPECT_EQ(ptr_r, &value);
    ASSERT_EQ(ptr.Get(), nullptr);
}

TEST(PtrViewOperatorTests, OperatorBinaryEquals)
{
    auto value{ 5 };
    auto same_value{ 5 };
    auto other_value{ 10 };

    ol::PtrView ptr{ &value };
    ol::PtrView ptr_copy{ &value };
    ol::PtrView ptr_same_value{ &same_value };
    ol::PtrView ptr_other{ &other_value };
    ol::PtrView<int> ptr_null{};

    EXPECT_FALSE(ptr == nullptr);
    EXPECT_FALSE(nullptr == ptr);
    EXPECT_FALSE(ptr == ptr_other);
    EXPECT_FALSE(ptr == ptr_same_value);
    EXPECT_TRUE(ptr == ptr_copy);
    EXPECT_TRUE(ptr_null == nullptr);
    ASSERT_TRUE(nullptr == ptr_null);
}

TEST(PtrViewOperatorTests, OperatorBinaryNotequals)
{
    auto value{ 5 };
    auto same_value{ 5 };
    auto other_value{ 10 };

    ol::PtrView ptr{ &value };
    ol::PtrView ptr_copy{ &value };
    ol::PtrView ptr_same_value{ &same_value };
    ol::PtrView ptr_other{ &other_value };
    ol::PtrView<int> ptr_null{};

    EXPECT_TRUE(ptr != nullptr);
    EXPECT_TRUE(nullptr != ptr);
    EXPECT_TRUE(ptr != ptr_other);
    EXPECT_TRUE(ptr != ptr_same_value);
    EXPECT_FALSE(ptr != ptr_copy);
    EXPECT_FALSE(ptr_null != nullptr);
    ASSERT_FALSE(nullptr != ptr_null);
}

TEST(PtrViewOperatorTests, OperatorLessThan)
{
    auto higher_value{ 5 };
    auto lower_value{ 10 };
    int* int_null = nullptr;

    ol::PtrView ptr_higher{ &higher_value };
    ol::PtrView ptr_lower{ &lower_value };
    ol::PtrView<int> ptr_null{};

    EXPECT_EQ(ptr_higher < ptr_lower, &higher_value < &lower_value);
    ASSERT_EQ(ptr_higher < ptr_null, &higher_value < int_null);
}

TEST(PtrViewOperatorTests, OperatorMoreThan)
{
    auto higher_value{ 5 };
    auto lower_value{ 10 };
    int* int_null = nullptr;

    ol::PtrView ptr_higher{ &higher_value };
    ol::PtrView ptr_lower{ &lower_value };
    ol::PtrView<int> ptr_null{};

    EXPECT_EQ(ptr_higher > ptr_lower, &higher_value > &lower_value);
    ASSERT_EQ(ptr_higher > ptr_null, &higher_value > int_null);
}

TEST(PtrViewOperatorTests, OperatorLessEqual)
{
    auto higher_value{ 5 };
    auto lower_value{ 10 };
    int* int_null = nullptr;

    ol::PtrView ptr_higher{ &higher_value };
    ol::PtrView ptr_lower{ &lower_value };
    ol::PtrView<int> ptr_null{};

    EXPECT_EQ(ptr_higher <= ptr_lower, &higher_value <= &lower_value);
    ASSERT_EQ(ptr_higher <= ptr_null, &higher_value <= int_null);
}

TEST(PtrViewOperatorTests, OperatorMoreEqual)
{
    auto higher_value{ 5 };
    auto lower_value{ 10 };
    int* int_null = nullptr;

    ol::PtrView ptr_higher{ &higher_value };
    ol::PtrView ptr_lower{ &lower_value };
    ol::PtrView<int> ptr_null{};

    EXPECT_EQ(ptr_higher >= ptr_lower, &higher_value >= &lower_value);
    ASSERT_EQ(ptr_higher >= ptr_null, &higher_value >= int_null);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
