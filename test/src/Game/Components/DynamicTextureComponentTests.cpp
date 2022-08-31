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
#include "Game/Components/DynamicTextureComponent.hpp"

namespace test
{

namespace ol = open_labora;

TEST(DynamicTextureComponentsTests, NeedsUpdate_TrueByDefault)
{
    auto component = ol::DynamicTextureComponent{};

    ASSERT_TRUE(component.NeedsUpdate());
}

TEST(DynamicTextureComponentsTests, NeedsUpdate_TrueAfterDefaultSetOutdated)
{
    auto component = ol::DynamicTextureComponent{};
    component.SetUpToDate(false);

    ASSERT_TRUE(component.NeedsUpdate());
}

TEST(DynamicTextureComponentsTests, NeedsUpdate_FalseAfterSetUpToDate)
{
    auto component = ol::DynamicTextureComponent{};
    component.SetUpToDate(true);

    ASSERT_FALSE(component.NeedsUpdate());
}

TEST(DynamicTextureComponentsTests, NeedsUpdate_TrueAfterSetOutated)
{
    auto component = ol::DynamicTextureComponent{};
    component.SetUpToDate(true);
    component.SetUpToDate(false);

    ASSERT_TRUE(component.NeedsUpdate());
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
