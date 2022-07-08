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
#include "Game/Components/PlotComponent.hpp"
#include "Game/Plot.hpp"

namespace test
{

namespace ol = open_labora;
using Type = ol::plot::Type;

static constexpr auto begin_value = static_cast<int>(Type::Begin);
static constexpr auto end_value = static_cast<int>(Type::End);
static constexpr auto range = end_value - begin_value;

TEST(TileOperatorsTests, OperatorPreincrement_Once)
{
    auto type = Type::Begin;

    ++type;

    ASSERT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::Central);
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
    ASSERT_EQ(type, Type::Central);
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
    ASSERT_EQ(type, Type::Central);
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

TEST(PlotComponentTests, GetType)
{
    auto plot = ol::PlotComponent(ol::plot::kCoastalPlotSpan,
                                  Type::Coastal,
                                  true);

    ASSERT_EQ(plot.GetType(), Type::Coastal);
}

TEST(PlotComponentTests, GetTileCount)
{
    auto plot = ol::PlotComponent(ol::plot::kCoastalPlotSpan,
                                  Type::Coastal,
                                  true);

    ASSERT_EQ(plot.GetTileCount(), ol::plot::kCoastalPlotSpan.size());
}

TEST(PlotComponentTests, GetTiles)
{
    auto plot = ol::PlotComponent(ol::plot::kCoastalPlotSpan,
                                  Type::Coastal,
                                  true);

    ASSERT_EQ(plot.GetTiles().data(), ol::plot::kCoastalPlotSpan.data());
}

TEST(PlotComponentTests, IsAlternative)
{
    auto plot = ol::PlotComponent(ol::plot::kCoastalPlotSpan,
                                  Type::Coastal,
                                  true);

    ASSERT_TRUE(plot.IsAlternative());
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
