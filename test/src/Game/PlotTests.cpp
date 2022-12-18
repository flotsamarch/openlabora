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
#include "Game/Plot.hpp"

namespace test
{

namespace ol = open_labora;

TEST(LotTests, TypeId_Constructor)
{
    bool ne_init{ false };

    for(auto i = 0; i < 10; ++i) {
        auto subtype = ol::lot::SubtypeId{ i };
        if (static_cast<int>(subtype) != i) {
            ne_init = true;
        }
    }

    ASSERT_FALSE(ne_init);
}

TEST(PlotTests, getPlots_AlwaysNotEmpty)
{
    bool was_empty{ false };

    for (auto type = ol::lot::Type::Begin; type < ol::lot::Type::End; ++type) {
        auto plots = ol::plot::getPlots(type);
        if (plots.empty()) {
            was_empty = true;
        }
    }

    ASSERT_FALSE(was_empty);
}

TEST(PlotTests, getPlots_PlotSizesAlwaysGreaterThanZero)
{
    bool was_empty{ false };

    for (auto type = ol::lot::Type::Begin; type < ol::lot::Type::End; ++type) {
        auto plots = ol::plot::getPlots(type);
        for (auto plot : plots) {
            if (plot.empty()) {
                was_empty = true;
            }
        }
    }

    ASSERT_FALSE(was_empty);
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
