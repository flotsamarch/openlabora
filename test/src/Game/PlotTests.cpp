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
#include <unordered_set>
#include <sstream>
#include "Game/Plot.hpp"

namespace test
{

namespace ol = open_labora;

testing::Message& operator<<(testing::Message& msg, ol::lot::Type type)
{
    return msg << "LotType = " << static_cast<int>(type);
}

TEST(LotTests, TypeId_Constructor)
{
    for(auto i = 0; i < 10; ++i) {
        auto subtype = ol::lot::SubtypeId{ i };
        ASSERT_EQ(static_cast<int>(subtype), i);
    }
}

TEST(PlotTests, getPlots_AlwaysNotEmpty)
{
    for (auto type : ol::EnumRange<ol::lot::Type>{}) {
        auto plots = ol::plot::getPlots(type);
        ASSERT_FALSE(plots.empty()) << "No plots defined for lot type: "
                                    << static_cast<int>(type);
    }
}

TEST(PlotTests, getPlots_PlotSizesAlwaysGreaterThanZero)
{
    for (auto type : ol::EnumRange<ol::lot::Type>{}) {
        auto plots = ol::plot::getPlots(type);
        for (auto plot : plots) {
            ASSERT_FALSE(plot.empty()) << "Empty plot defined for lot type: "
                                       << static_cast<int>(type);
        }
    }
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
