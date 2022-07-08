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
#include "Game/Tile.hpp"

namespace test
{

using Type = open_labora::tile::Type;
using TileInfo = open_labora::tile::TileInfo;

static constexpr auto begin_value = static_cast<int>(Type::Begin);
static constexpr auto end_value = static_cast<int>(Type::End);
static constexpr auto range = end_value - begin_value;

TEST(TileOperatorsTests, OperatorPreincrement_Once)
{
    auto type = Type::Begin;

    ++type;

    ASSERT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::Forest);
}

TEST(TileOperatorsTests, OperatorPreincrement_Loop)
{
    auto type = Type::Begin;
    for (auto i = 0; i < range; ++i) {
        ++type;
    }

    EXPECT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::End);
}

TEST(TileOperatorsTests, OperatorPlusLeft_PlusOne)
{
    auto type = Type::Begin;

    type = type + 1;

    ASSERT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::Forest);
}

TEST(TileOperatorsTests, OperatorPlusLeft_PlusRange)
{
    auto type = Type::Begin;

    type = type + range;

    ASSERT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::End);
}

TEST(TileOperatorsTests, OperatorPlusRight_PlusOne)
{
    auto type = Type::Begin;

    type = 1 + type;

    ASSERT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::Forest);
}

TEST(TileOperatorsTests, OperatorPlusRight_PlusRange)
{
    auto type = Type::Begin;

    type = range + type;

    ASSERT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::End);
}

TEST(TileOperatorsTests, OperatorPlusLeft_BigNumber)
{
    constexpr auto very_big_number = static_cast<int>(Type::End) + 999999;

    ASSERT_EQ(Type::Begin + very_big_number, Type::End);
}

TEST(TileOperatorsTests, OperatorPlusRight_BigNumber)
{
    constexpr auto very_big_number = static_cast<int>(Type::End) + 999999;

    ASSERT_EQ(very_big_number + Type::Begin, Type::End);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_Default)
{
    TileInfo one, two;

    EXPECT_TRUE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_ValidDifferent)
{
    TileInfo one, two;

    one.valid = true;

    EXPECT_FALSE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_ValidSame)
{
    TileInfo one, two;

    one.valid = true;
    two.valid = true;

    EXPECT_TRUE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_TypeDifferent)
{
    TileInfo one, two;

    one.type = Type::Begin + 1;

    EXPECT_FALSE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_TypeSame)
{
    TileInfo one, two;

    one.type = Type::Begin + 1;
    two.type = Type::Begin + 1;

    EXPECT_TRUE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_CoordXDifferent)
{
    TileInfo one, two;

    one.coord.x = 1.5f;

    EXPECT_FALSE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_CoordXSame)
{
    TileInfo one, two;

    one.coord.x = 1.5f;
    two.coord.x = 1.5f;

    EXPECT_TRUE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_CoordYDifferent)
{
    TileInfo one, two;

    one.coord.y = 5.52345234f;

    EXPECT_FALSE(one == two);
}

TEST(TileInfoOperatorsTests, TileInfoOperatorEquals_CoordYSame)
{
    TileInfo one, two;

    one.coord.y = 5.52345234f;
    two.coord.y = 5.52345234f;

    EXPECT_TRUE(one == two);
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
