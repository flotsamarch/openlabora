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
#include "Game/Components/EffectiveInteractionAreaComponent.hpp"

using OpenLabora::EffectiveInteractionAreaComponent;

namespace Test
{

TEST(EffectiveInteractionAreaTests, GetOffset_ShapeCopyCtor)
{
    const auto offset = sf::Vector2f{ 10.f, 12.f };
    auto shape = sf::RectangleShape{ { 0.f, 0.f } };
    auto component = EffectiveInteractionAreaComponent(shape, offset);

    auto get_offset = component.GetOffset();
    EXPECT_FLOAT_EQ(get_offset.x, offset.x);
    ASSERT_FLOAT_EQ(get_offset.y, offset.y);
}

TEST(EffectiveInteractionAreaTests, GetOffset_ShapeMoveCtor)
{
    const auto offset = sf::Vector2f{ 12.f, 14.f };
    auto shape = sf::RectangleShape{ { 0.f, 0.f } };
    auto component = EffectiveInteractionAreaComponent(std::move(shape), offset);

    auto get_offset = component.GetOffset();
    EXPECT_FLOAT_EQ(get_offset.x, offset.x);
    ASSERT_FLOAT_EQ(get_offset.y, offset.y);
}

TEST(EffectiveInteractionAreaTests, SetOffset)
{
    const auto offset = sf::Vector2f{ 100.f, 2.f };
    auto shape = sf::RectangleShape{ { 0.f, 0.f } };
    auto component = EffectiveInteractionAreaComponent(shape, {});

    component.SetOffset(offset);

    auto get_offset = component.GetOffset();
    EXPECT_FLOAT_EQ(get_offset.x, offset.x);
    ASSERT_FLOAT_EQ(get_offset.y, offset.y);
}

TEST(EffectiveInteractionAreaTests, IsPointInArea_TrueNoOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto component = EffectiveInteractionAreaComponent(shape, {});
    auto point = sf::Vector2f{ 2.f, 9.f };

    ASSERT_TRUE(component.IsPointInArea(point));
}

TEST(EffectiveInteractionAreaTests, IsPointInArea_FalseNoOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto component = EffectiveInteractionAreaComponent(shape, {});
    auto point = sf::Vector2f{ -1.f, 19.f };

    ASSERT_FALSE(component.IsPointInArea(point));
}

TEST(EffectiveInteractionAreaTests, IsPointInArea_TrueOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto offset = sf::Vector2f{ 5.f, 8.f };
    auto component = EffectiveInteractionAreaComponent(shape, offset);
    auto point = sf::Vector2f{ 9.f, 15.f };

    ASSERT_TRUE(component.IsPointInArea(point));
}

TEST(EffectiveInteractionAreaTests, IsPointInArea_FalseOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto offset = sf::Vector2f{ 8.f, 5.f };
    auto component = EffectiveInteractionAreaComponent(shape, offset);
    auto point = sf::Vector2f{ 6.f, 3.f };

    ASSERT_FALSE(component.IsPointInArea(point));
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
