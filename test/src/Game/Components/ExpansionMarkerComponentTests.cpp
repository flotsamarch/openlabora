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
#include <gmock/gmock.h>
#include "Game/Components/ExpansionMarkerComponent.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"

namespace Test
{

using ExpansionMarkerComponentTests = ResourceManagerDefaultActionTestBase;
using OpenLabora::ExpansionMarkerComponent;
using OpenLabora::PlotComponent;
using OpenLabora::PositionComponent;
using OpenLabora::ecs::getComponent;
using PlotType = OpenLabora::plot::Type;
using MarkerType = OpenLabora::marker::Type;

TEST_F(ExpansionMarkerComponentTests, GetPlots)
{
    constexpr auto type = PlotType::Begin;
    const auto position = sf::Vector2f{ 5.f, 10.f };
    auto plot = OpenLabora::plot::create(PlotType::Begin,
                                         position,
                                         mResourceMgr);

    auto component = ExpansionMarkerComponent(MarkerType::Begin, plot, plot);

    auto&& [plot1, plot2] = component.GetPlots();
    auto&& plot1_cmpnt = getComponent<PlotComponent>(plot1.get());
    auto&& plot2_cmpnt = getComponent<PlotComponent>(plot2.get());

    auto&& plot1_pos = getComponent<PositionComponent>(plot1.get());
    auto&& plot2_pos = getComponent<PositionComponent>(plot2.get());

    EXPECT_EQ(plot1_cmpnt.GetType(), type);
    EXPECT_EQ(plot2_cmpnt.GetType(), type);
    EXPECT_FLOAT_EQ(plot1_pos.position.x, position.x);
    EXPECT_FLOAT_EQ(plot1_pos.position.y, position.y);
    EXPECT_FLOAT_EQ(plot2_pos.position.x, position.x);
    ASSERT_FLOAT_EQ(plot2_pos.position.y, position.y);
}

TEST_F(ExpansionMarkerComponentTests, GetType)
{
    constexpr auto type = MarkerType::Begin;
    auto plot = OpenLabora::plot::create(PlotType::Begin, {}, mResourceMgr);
    auto component = ExpansionMarkerComponent(type, plot, plot);

    ASSERT_EQ(component.GetType(), type);
}

TEST_F(ExpansionMarkerComponentTests, GetPlotType)
{
    constexpr auto type = PlotType::Begin;
    auto plot = OpenLabora::plot::create(type, {}, mResourceMgr);
    auto component = ExpansionMarkerComponent(MarkerType::Begin, plot, plot);

    ASSERT_EQ(component.GetPlotType(), type);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
