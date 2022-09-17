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
#include "Game/Components/InteractionAreaComponent.hpp"

using open_labora::InteractionAreaComponent;

namespace test
{

TEST(InteractionAreaTests, GetOffset_ShapeCopyCtor)
{
    const auto offset = sf::Vector2f{ 10.f, 12.f };
    auto shape = sf::RectangleShape{ { 0.f, 0.f } };
    auto area = InteractionAreaComponent(shape, offset);

    auto get_offset = area.GetOffset();
    EXPECT_FLOAT_EQ(get_offset.x, offset.x);
    ASSERT_FLOAT_EQ(get_offset.y, offset.y);
}

TEST(InteractionAreaTests, GetOffset_ShapeMoveCtor)
{
    const auto offset = sf::Vector2f{ 12.f, 14.f };
    auto shape = sf::RectangleShape{ { 0.f, 0.f } };
    auto area = InteractionAreaComponent(std::move(shape), offset);

    auto get_offset = area.GetOffset();
    EXPECT_FLOAT_EQ(get_offset.x, offset.x);
    ASSERT_FLOAT_EQ(get_offset.y, offset.y);
}

TEST(InteractionAreaTests, SetOffset)
{
    const auto offset = sf::Vector2f{ 100.f, 2.f };
    auto shape = sf::RectangleShape{ { 0.f, 0.f } };
    auto area = InteractionAreaComponent(shape, {});

    area.SetOffset(offset);

    auto get_offset = area.GetOffset();
    EXPECT_FLOAT_EQ(get_offset.x, offset.x);
    ASSERT_FLOAT_EQ(get_offset.y, offset.y);
}

TEST(InteractionAreaTests, IsPointInArea_TrueNoOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto area = InteractionAreaComponent(shape, {});
    auto point = sf::Vector2f{ 2.f, 9.f };

    ASSERT_TRUE(area.IsPointInArea(point));
}

TEST(InteractionAreaTests, IsPointInArea_FalseNoOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto area = InteractionAreaComponent(shape, {});
    auto point = sf::Vector2f{ -1.f, 19.f };

    ASSERT_FALSE(area.IsPointInArea(point));
}

TEST(InteractionAreaTests, IsPointInArea_TrueOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto offset = sf::Vector2f{ 5.f, 8.f };
    auto area = InteractionAreaComponent(shape, offset);
    auto point = sf::Vector2f{ 9.f, 15.f };

    ASSERT_TRUE(area.IsPointInArea(point));
}

TEST(InteractionAreaTests, IsPointInArea_FalseOffset)
{
    auto shape = sf::RectangleShape{ { 10.f, 10.f } };
    auto offset = sf::Vector2f{ 8.f, 5.f };
    auto area = InteractionAreaComponent(shape, offset);
    auto point = sf::Vector2f{ 6.f, 3.f };

    ASSERT_FALSE(area.IsPointInArea(point));
}

TEST(InteractionAreaTests, SetShape_ChangesShape)
{
    auto shape1 = sf::RectangleShape{ { 10.f, 10.f } };
    auto shape2 = sf::RectangleShape{ { 20.f, 30.f } };
    auto area = InteractionAreaComponent(shape1, {});
    auto point = sf::Vector2f{ 12.f, 19.f };

    auto is_in_area_before = area.IsPointInArea(point);
    area.SetShape(shape2);

    EXPECT_FALSE(is_in_area_before);
    ASSERT_TRUE(area.IsPointInArea(point));
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
