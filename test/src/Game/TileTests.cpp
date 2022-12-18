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

namespace ol = open_labora;

using Type = ol::tile::Type;
using TileInfo = ol::TileInfo;

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
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
