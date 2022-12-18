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
#include <ecs.hpp/ecs.hpp>
#include "ECS/MassAssignComponents.hpp"

namespace test
{

namespace ol = open_labora;

namespace
{

struct TestComponent1
{
    bool flag = false;
};

struct TestComponent2
{
    float x = 0.f;
    float y = 0.f;
};

} // namespace anonymous

TEST(MassAssignComponentsTests, NoComponentsByDefault)
{
    auto registry = ecs_hpp::registry{};
    auto entity = ol::Entity{ registry.create_entity() };
    auto assign = ol::MassAssignComponents{ entity };

    ASSERT_EQ(entity.GetComponentCount(), 0);
}

TEST(MassAssignComponentsTests, AssingSingleComponent)
{
    auto registry = ecs_hpp::registry{};
    auto entity = ol::Entity{ registry.create_entity() };
    auto assign = ol::MassAssignComponents{ entity };

    assign.Assign<TestComponent1>();

    EXPECT_TRUE(entity.HasComponent<TestComponent1>());
    EXPECT_FALSE(entity.GetComponent<TestComponent1>().flag);
    ASSERT_EQ(entity.GetComponentCount(), 1);
}

TEST(MassAssignComponentsTests, AssingSingleComponentWithArguments)
{
    auto registry = ecs_hpp::registry{};
    auto entity = ol::Entity{ registry.create_entity() };
    auto assign = ol::MassAssignComponents{ entity };

    assign.Assign<TestComponent1>(true);

    EXPECT_TRUE(entity.HasComponent<TestComponent1>());
    EXPECT_TRUE(entity.GetComponent<TestComponent1>().flag);
    ASSERT_EQ(entity.GetComponentCount(), 1);
}

TEST(MassAssignComponentsTests, AssingMultipleComponents)
{
    auto registry = ecs_hpp::registry{};
    auto entity = ol::Entity{ registry.create_entity() };
    auto assign = ol::MassAssignComponents{ entity };

    assign.Assign<TestComponent1>()
        .Assign<TestComponent2>();

    EXPECT_TRUE(entity.HasComponent<TestComponent1>());
    EXPECT_FALSE(entity.GetComponent<TestComponent1>().flag);
    EXPECT_TRUE(entity.HasComponent<TestComponent2>());
    EXPECT_FLOAT_EQ(entity.GetComponent<TestComponent2>().x, 0.f);
    EXPECT_FLOAT_EQ(entity.GetComponent<TestComponent2>().y, 0.f);
    ASSERT_EQ(entity.GetComponentCount(), 2);
}

TEST(MassAssignComponentsTests, AssingMultipleComponentsWithArguments)
{
    auto registry = ecs_hpp::registry{};
    auto entity = ol::Entity{ registry.create_entity() };
    auto assign = ol::MassAssignComponents{ entity };

    assign.Assign<TestComponent1>(true)
        .Assign<TestComponent2>(1.f, 2.f);

    EXPECT_TRUE(entity.HasComponent<TestComponent1>());
    EXPECT_TRUE(entity.GetComponent<TestComponent1>().flag);
    EXPECT_TRUE(entity.HasComponent<TestComponent2>());
    EXPECT_FLOAT_EQ(entity.GetComponent<TestComponent2>().x, 1.f);
    EXPECT_FLOAT_EQ(entity.GetComponent<TestComponent2>().y, 2.f);
    ASSERT_EQ(entity.GetComponentCount(), 2);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
