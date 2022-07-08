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

namespace test
{

namespace ol = open_labora;
using MarkerComponent = ol::ExpansionMarkerComponent;

using ExpansionMarkerComponentTests = ResourceManagerDefaultActionTestBase;

TEST_F(ExpansionMarkerComponentTests, GetPlots)
{
    constexpr auto type = ol::plot::Type::Begin;
    const auto position = sf::Vector2f{ 5.f, 10.f };
    auto plot = ol::plot::create(ol::plot::Type::Begin,
                                 position,
                                 mResourceMgr);

    auto component = MarkerComponent(ol::marker::Type::Begin, plot, plot);

    auto&& [plot1, plot2] = component.GetPlots();
    auto&& plot1_cmpnt = ol::ecs::getComponent<ol::PlotComponent>(plot1.get());
    auto&& plot2_cmpnt = ol::ecs::getComponent<ol::PlotComponent>(plot2.get());

    auto&& plot1_pos = ol::ecs::getComponent<ol::PositionComponent>(plot1.get());
    auto&& plot2_pos = ol::ecs::getComponent<ol::PositionComponent>(plot2.get());

    EXPECT_EQ(plot1_cmpnt.GetType(), type);
    EXPECT_EQ(plot2_cmpnt.GetType(), type);
    EXPECT_FLOAT_EQ(plot1_pos.position.x, position.x);
    EXPECT_FLOAT_EQ(plot1_pos.position.y, position.y);
    EXPECT_FLOAT_EQ(plot2_pos.position.x, position.x);
    ASSERT_FLOAT_EQ(plot2_pos.position.y, position.y);
}

TEST_F(ExpansionMarkerComponentTests, GetType)
{
    constexpr auto type = ol::marker::Type::Begin;
    auto plot = ol::plot::create(ol::plot::Type::Begin, {}, mResourceMgr);
    auto component = MarkerComponent(type, plot, plot);

    ASSERT_EQ(component.GetType(), type);
}

TEST_F(ExpansionMarkerComponentTests, GetPlotType)
{
    constexpr auto type = ol::plot::Type::Begin;
    auto plot = ol::plot::create(type, {}, mResourceMgr);
    auto component = MarkerComponent(ol::marker::Type::Begin, plot, plot);

    ASSERT_EQ(component.GetPlotType(), type);
}

TEST_F(ExpansionMarkerComponentTests, SetPlotPositions)
{
    using ol::ecs::getComponent;
    using ol::PositionComponent;

    constexpr auto x = 15.887f;
    constexpr auto y = 92.345f;
    auto plot = ol::plot::create(ol::plot::Type::Begin, {}, mResourceMgr);
    auto component = MarkerComponent(ol::marker::Type::Begin, plot, plot);
    auto plots = component.GetPlots();
    auto&& plot_cmpnt = getComponent<PositionComponent>(plots.first.get());
    auto&& plot_alt_cmpnt = getComponent<PositionComponent>(plots.second.get());

    component.SetPlotPositions({x, y});
    EXPECT_FLOAT_EQ(plot_cmpnt.position.x, x);
    EXPECT_FLOAT_EQ(plot_cmpnt.position.y, y);
    EXPECT_GE(plot_alt_cmpnt.position.x, x);
    ASSERT_GE(plot_alt_cmpnt.position.y, y);
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
