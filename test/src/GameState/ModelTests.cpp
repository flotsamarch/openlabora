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
#include "GameState/Model.hpp"

namespace test
{

namespace ol = open_labora;

TEST(ModelTests, IsPaused_NotPausedByDefault)
{
    ol::Model model;
    ASSERT_FALSE(model.IsPaused());
}

TEST(ModelTests, IsPaused_SetNotPaused)
{
    ol::Model model;

    model.SetPaused(false);

    ASSERT_FALSE(model.IsPaused());
}

TEST(ModelTests, IsPaused_Pause)
{
    ol::Model model;

    model.SetPaused(true);

    ASSERT_TRUE(model.IsPaused());
}

TEST(ModelTests, IsPaused_Unpause)
{
    ol::Model model;

    model.SetPaused(true);
    model.SetPaused(false);

    ASSERT_FALSE(model.IsPaused());
}

TEST(ModelTests, IsPaused_Paused_SetPaused)
{
    ol::Model model;

    model.SetPaused(false);
    model.SetPaused(true);

    ASSERT_TRUE(model.IsPaused());
}

TEST(ModelTests, GetDrawableObjects_EmptyByDefault)
{
    ol::Model model;

    auto objects = model.GetDrawableObjects();

    ASSERT_TRUE(objects.IsEmpty());
}

TEST(ModelTests, ClearDrawableObjects_DoesNotAddObjects)
{
    ol::Model model;

    model.ClearDrawableObjects();
    auto objects = model.GetDrawableObjects();

    ASSERT_TRUE(objects.IsEmpty());
}

TEST(ModelTests, GetDrawableObject_AddDrawableObjectIncreasesObjectCount)
{
    constexpr auto sprite_count = 5;
    ol::Model model;
    std::vector<ol::Sprite> sprites{ sprite_count };

    for (auto&& sprite : sprites) {
        model.AddDrawableObject(sprite);
    }

    auto objects = model.GetDrawableObjects();

    ASSERT_EQ(objects.GetSize(), sprite_count);
}

TEST(ModelTests, GetDrawableObject_ClearDrawableObjectsRemovesAllObjects)
{
    constexpr auto sprite_count = 5;
    ol::Model model;
    std::vector<ol::Sprite> sprites{ sprite_count };

    for (auto&& sprite : sprites) {
        model.AddDrawableObject(sprite);
    }

    model.ClearDrawableObjects();
    auto objects = model.GetDrawableObjects();

    ASSERT_TRUE(objects.IsEmpty());
}

TEST(ModelTests, GetWorldMousePosition_0_0_ByDefault)
{
    ol::Model model;

    auto position = model.GetWorldMousePosition();

    EXPECT_FLOAT_EQ(position.x, 0.f);
    ASSERT_FLOAT_EQ(position.y, 0.f);
}

TEST(ModelTests, GetWorldMousePosition_ChangedBySetWorldMousePosition)
{
    constexpr auto position_x = 58.f;
    constexpr auto position_y = 4379.f;
    ol::Model model;

    model.SetWorldMousePosition({ position_x, position_y });
    auto position = model.GetWorldMousePosition();

    EXPECT_FLOAT_EQ(position.x, position_x);
    ASSERT_FLOAT_EQ(position.y, position_y);
}

} // namespace test

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
