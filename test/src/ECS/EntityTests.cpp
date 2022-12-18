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
#include "ECS/Entity.hpp"

namespace test
{

namespace ol = open_labora;

namespace
{

struct TestComponent1
{
    TestComponent1() = default;
    TestComponent1(bool _flag) : flag{ _flag } {};

    bool flag{ false };
};

class TestComponent2
{
};

} // namespace anonymous

class EntityTests : public testing::Test
{
    ecs_hpp::registry mRegistry{};

protected:
    ol::Entity mEntity{ mRegistry.create_entity() };
};

class ConstEntityTests : public testing::Test
{
    ecs_hpp::registry mRegistry{};
    ecs_hpp::entity mLibEntity{ mRegistry.create_entity() };

protected:
    ol::Entity mEntity{ mLibEntity };
    ol::ConstEntity mConstEntity{ mLibEntity };
};

TEST_F(EntityTests, IsValid_TrueByDefault)
{
    ASSERT_TRUE(mEntity.IsValid());
}

TEST(EntityIdTests, GetId_UniqueIds)
{
    constexpr auto entity_count = 10;
    auto registry = ecs_hpp::registry{};
    auto ids = std::unordered_set<ol::EntityId>{};

    for (auto i = 0; i < entity_count; ++i) {
        auto entity = ol::Entity(registry.create_entity());
        ids.insert(entity.GetId());
    }

    ASSERT_EQ(ids.size(), entity_count);
}

TEST_F(EntityTests, Destroy_InvalidatesEntity)
{
    mEntity.Destroy();

    ASSERT_FALSE(mEntity.IsValid());
}

TEST_F(EntityTests, GetComponentCount_ZeroByDefault)
{
    ASSERT_EQ(mEntity.GetComponentCount(), 0);
}

TEST_F(EntityTests, HasComponent_FalseByDefault)
{
    ASSERT_FALSE(mEntity.HasComponent<TestComponent1>());
}

TEST_F(EntityTests, GetComponentCount_IncreasedByAssignComponent)
{
    mEntity.AssignComponent<TestComponent1>();

    ASSERT_EQ(mEntity.GetComponentCount(), 1);
}

TEST_F(EntityTests, AssignComponent_DoesNotIncreaseComponentCountWhenNotUnique)
{
    mEntity.AssignComponent<TestComponent1>();
    mEntity.AssignComponent<TestComponent1>();

    ASSERT_EQ(mEntity.GetComponentCount(), 1);
}

TEST_F(EntityTests, GetComponentCount_IncreasedByAssignComponentWhenUnique)
{
    mEntity.AssignComponent<TestComponent1>();
    mEntity.AssignComponent<TestComponent2>();

    ASSERT_EQ(mEntity.GetComponentCount(), 2);
}

TEST_F(EntityTests, AssignComponent_ReassignsValue)
{
    auto&& component = mEntity.AssignComponent<TestComponent1>(false);
    mEntity.AssignComponent<TestComponent1>(true);

    ASSERT_TRUE(component.flag);
}

TEST_F(EntityTests, Clone)
{
    mEntity.AssignComponent<TestComponent1>();
    mEntity.AssignComponent<TestComponent2>();

    auto cloned_entity = mEntity.Clone();

    EXPECT_TRUE(cloned_entity.IsValid());
    EXPECT_NE(cloned_entity.GetId(), mEntity.GetId());
    EXPECT_TRUE(cloned_entity.HasComponent<TestComponent1>());
    EXPECT_TRUE(cloned_entity.HasComponent<TestComponent2>());
    ASSERT_EQ(cloned_entity.GetComponentCount(), 2);
}

TEST_F(EntityTests, HasComponent_TrueAfterAssignComponent)
{
    mEntity.AssignComponent<TestComponent1>();

    ASSERT_TRUE(mEntity.HasComponent<TestComponent1>());
}

TEST_F(EntityTests, GetOrCreateComponent_IncreasesComponentCount)
{
    mEntity.GetOrCreateComponent<TestComponent1>();

    ASSERT_EQ(mEntity.GetComponentCount(), 1);
}

TEST_F(EntityTests, GetOrCreateComponent_DoesNotIncreaseComponentCountOnSecondCall)
{
    mEntity.GetOrCreateComponent<TestComponent1>();
    mEntity.GetOrCreateComponent<TestComponent1>();

    ASSERT_EQ(mEntity.GetComponentCount(), 1);
}

TEST_F(EntityTests, GetOrCreateComponent_DoesNotReassignValue)
{
    auto&& before = mEntity.GetOrCreateComponent<TestComponent1>(false);
    auto&& after = mEntity.GetOrCreateComponent<TestComponent1>(true);

    EXPECT_EQ(before.flag, after.flag);
    ASSERT_EQ(after.flag, false);
}

TEST_F(EntityTests, GetComponentCount_DoesNotGoNegative)
{
    auto result = mEntity.RemoveComponent<TestComponent1>();

    EXPECT_FALSE(result);
    ASSERT_EQ(mEntity.GetComponentCount(), 0);
}

TEST_F(EntityTests, GetComponentCount_DecreasedByRemoveComponent)
{
    mEntity.AssignComponent<TestComponent1>();
    auto count_before_removal = mEntity.GetComponentCount();
    auto result = mEntity.RemoveComponent<TestComponent1>();

    EXPECT_TRUE(result);
    EXPECT_EQ(count_before_removal, 1);
    ASSERT_EQ(mEntity.GetComponentCount(), 0);
}

TEST_F(EntityTests, RemoveAllComponents_DoesNothingByDefault)
{
    auto result = mEntity.RemoveAllComponents();

    EXPECT_EQ(result, 0);
    ASSERT_EQ(mEntity.GetComponentCount(), 0);
}

TEST_F(EntityTests, GetComponentCount_DecreasedByRemoveAllComponents)
{
    mEntity.AssignComponent<TestComponent1>();
    mEntity.AssignComponent<TestComponent2>();
    auto count_before_removal = mEntity.GetComponentCount();
    auto result = mEntity.RemoveAllComponents();

    EXPECT_EQ(count_before_removal, 2);
    EXPECT_EQ(result, count_before_removal);
    ASSERT_EQ(mEntity.GetComponentCount(), 0);
}

TEST_F(EntityTests, GetComponent)
{
    auto&& before = mEntity.AssignComponent<TestComponent1>();
    bool flag_before = before.flag;

    auto&& component = mEntity.GetComponent<TestComponent1>();
    component.flag = true;

    EXPECT_FALSE(flag_before);
    ASSERT_TRUE(before.flag);
}

TEST_F(EntityTests, GetComponentConst)
{
    auto&& component = mEntity.AssignComponent<TestComponent1>();
    bool flag_before = component.flag;

    auto&& const_ref = std::as_const(mEntity).GetComponent<TestComponent1>();
    component.flag = true;

    EXPECT_FALSE(flag_before);
    ASSERT_TRUE(const_ref.flag);
}

TEST_F(EntityTests, FindComponent_NullByDefault)
{
    auto component = mEntity.FindComponent<TestComponent1>();

    ASSERT_EQ(component, nullptr);
}

TEST_F(EntityTests, FindComponent)
{
    auto&& before = mEntity.AssignComponent<TestComponent1>();
    bool flag_before = before.flag;

    auto component = mEntity.FindComponent<TestComponent1>();
    component->flag = true;

    EXPECT_FALSE(flag_before);
    ASSERT_TRUE(before.flag);
}

TEST_F(EntityTests, FindComponentConst)
{
    auto&& component = mEntity.AssignComponent<TestComponent1>();
    bool flag_before = component.flag;

    auto const_ptr = std::as_const(mEntity).FindComponent<TestComponent1>();
    component.flag = true;

    EXPECT_FALSE(flag_before);
    ASSERT_TRUE(const_ptr->flag);
}

TEST_F(ConstEntityTests, IsValid_TrueByDefault)
{
    ASSERT_TRUE(mConstEntity.IsValid());
}

TEST(EntityIdTests, ConstGetId_UniqueIds)
{
    constexpr auto entity_count = 10;
    auto registry = ecs_hpp::registry{};
    auto ids = std::unordered_set<ol::EntityId>{};

    for (auto i = 0; i < entity_count; ++i) {
        auto entity = ol::ConstEntity(registry.create_entity());
        ids.insert(entity.GetId());
    }

    ASSERT_EQ(ids.size(), entity_count);
}

TEST_F(ConstEntityTests, Destroy_InvalidatesEntity)
{
    mEntity.Destroy();

    ASSERT_FALSE(mConstEntity.IsValid());
}

TEST_F(ConstEntityTests, GetComponentCount_ZeroByDefault)
{
    ASSERT_EQ(mConstEntity.GetComponentCount(), 0);
}

TEST_F(ConstEntityTests, HasComponent_FalseByDefault)
{
    ASSERT_FALSE(mConstEntity.HasComponent<TestComponent1>());
}

TEST_F(ConstEntityTests, GetComponentCount_IncreasedByAssignComponent)
{
    mEntity.AssignComponent<TestComponent1>();

    ASSERT_EQ(mConstEntity.GetComponentCount(), 1);
}

TEST_F(ConstEntityTests,
       GetComponentCount_DoesNotGetIncreasedWhenNotUniqueAssigned)
{
    mEntity.AssignComponent<TestComponent1>();
    mEntity.AssignComponent<TestComponent1>();

    ASSERT_EQ(mConstEntity.GetComponentCount(), 1);
}

TEST_F(ConstEntityTests,
       GetComponentCount_IncreasedByAssignComponentWhenUnique)
{
    mEntity.AssignComponent<TestComponent1>();
    mEntity.AssignComponent<TestComponent2>();

    ASSERT_EQ(mConstEntity.GetComponentCount(), 2);
}

TEST_F(ConstEntityTests, HasComponent_TrueAfterAssignComponent)
{
    mEntity.AssignComponent<TestComponent1>();

    ASSERT_TRUE(mConstEntity.HasComponent<TestComponent1>());
}

TEST_F(ConstEntityTests, GetOrCreateComponent_IncreasesComponentCount)
{
    mEntity.GetOrCreateComponent<TestComponent1>();

    ASSERT_EQ(mConstEntity.GetComponentCount(), 1);
}

TEST_F(ConstEntityTests,
       GetOrCreateComponent_DoesNotIncreaseComponentCountOnSecondCall)
{
    mEntity.GetOrCreateComponent<TestComponent1>();
    mEntity.GetOrCreateComponent<TestComponent1>();

    ASSERT_EQ(mConstEntity.GetComponentCount(), 1);
}

TEST_F(ConstEntityTests, GetComponentCount_DoesNotGoNegative)
{
    auto result = mEntity.RemoveComponent<TestComponent1>();

    EXPECT_FALSE(result);
    ASSERT_EQ(mConstEntity.GetComponentCount(), 0);
}

TEST_F(ConstEntityTests, GetComponentCount_DecreasedByRemoveComponent)
{
    mEntity.AssignComponent<TestComponent1>();
    auto count_before_removal = mEntity.GetComponentCount();
    auto result = mEntity.RemoveComponent<TestComponent1>();

    EXPECT_TRUE(result);
    EXPECT_EQ(count_before_removal, 1);
    ASSERT_EQ(mConstEntity.GetComponentCount(), 0);
}

TEST_F(ConstEntityTests, GetComponentCount_DecreasedByRemoveAllComponents)
{
    mEntity.AssignComponent<TestComponent1>();
    mEntity.AssignComponent<TestComponent2>();
    auto count_before_removal = mEntity.GetComponentCount();
    auto result = mEntity.RemoveAllComponents();

    EXPECT_EQ(count_before_removal, 2);
    EXPECT_EQ(result, count_before_removal);
    ASSERT_EQ(mConstEntity.GetComponentCount(), 0);
}

TEST_F(ConstEntityTests, GetComponent)
{
    auto&& component = mEntity.AssignComponent<TestComponent1>();
    bool flag_before = component.flag;

    auto&& const_ref = std::as_const(mEntity).GetComponent<TestComponent1>();
    component.flag = true;

    EXPECT_FALSE(flag_before);
    ASSERT_TRUE(const_ref.flag);
}

TEST_F(ConstEntityTests, FindComponent_NullByDefault)
{
    auto component = mConstEntity.FindComponent<TestComponent1>();

    ASSERT_EQ(component, nullptr);
}

TEST_F(ConstEntityTests, FindComponent)
{
    auto&& component = mEntity.AssignComponent<TestComponent1>();
    bool flag_before = component.flag;

    auto const_ptr = std::as_const(mEntity).FindComponent<TestComponent1>();
    component.flag = true;

    EXPECT_FALSE(flag_before);
    ASSERT_TRUE(const_ptr->flag);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}
