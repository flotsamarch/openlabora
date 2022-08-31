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
#include "Game/Components/PositionComponent.hpp"

namespace test
{

namespace ol = open_labora;

TEST(PositionComponentTests, DefaultConstructor)
{
    auto component = ol::PositionComponent{};

    EXPECT_FLOAT_EQ(component.x, 0.f);
    ASSERT_FLOAT_EQ(component.y, 0.f);
}

TEST(PositionComponentTests, Constructor)
{
    constexpr auto value_x{ 3489.f };
    constexpr auto value_y{ 209.f };

    auto component = ol::PositionComponent{ value_x, value_y };

    EXPECT_FLOAT_EQ(component.x, value_x);
    ASSERT_FLOAT_EQ(component.y, value_y);
}

TEST(PositionComponentTests, ConstructorFromVector)
{
    constexpr auto value_x{ 349.f };
    constexpr auto value_y{ 290.f };

    auto component = ol::PositionComponent{ ol::Vector2f{ value_x, value_y } };

    EXPECT_FLOAT_EQ(component.x, value_x);
    ASSERT_FLOAT_EQ(component.y, value_y);
}

TEST(PositionComponentTests, OperatorVector)
{
    constexpr auto value_x{ 489.f };
    constexpr auto value_y{ 2900.f };

    auto component = ol::PositionComponent{ value_x, value_y };
    auto vector = ol::Vector2f{ component };

    EXPECT_FLOAT_EQ(vector.x, value_x);
    ASSERT_FLOAT_EQ(vector.y, value_y);
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
