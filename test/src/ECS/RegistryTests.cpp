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
#include "ECS/Registry.hpp"
#include "ECS/Feature.hpp"
#include "ECS/System.hpp"
#include "ECS/Predicates.hpp"
#include "Misc/CommonTypedefs.hpp"

namespace test
{

namespace ol = open_labora;

class RegistryTests : public testing::Test
{
protected:
    ol::Registry mRegistry;
};

namespace
{

struct TestComponent1
{
    bool flag{ false };
};

struct TestComponent2
{
    float x{ 0.f };
    float y{ 0.f };
};

struct TestComponent3{}; // Never added to anything

struct TestFeature{};
struct TestEvent{};

struct TestSystem : ol::System<TestSystem, TestEvent>
{
    bool& flag;

    TestSystem(bool& _flag) : flag{ _flag } {};
};

void systemHandleEvent(TestSystem& system, ol::RegistryRef, const TestEvent&)
{
    system.flag = true;
}

} // namespace anonymous

class RegistryWithEntitiesTests : public RegistryTests
{
protected:
    static constexpr auto kHasOnlyBoolComponentCount{ 9u };
    static constexpr auto kHasBothComponentsCount{ 7u };
    static constexpr auto kHasOnlyFloatComponentCount{ 5u };
    static constexpr auto kHasNoComponentsCount{ 3u };

public:
    RegistryWithEntitiesTests() {
        for( auto i{ 0u }; i < kHasNoComponentsCount; ++i) {
            mRegistry.CreateEntity();
        }

        for( auto i{ 0u }; i < kHasOnlyBoolComponentCount; ++i) {
            mRegistry.CreateEntity()
                .AssignComponent<TestComponent1>();
        }

        for( auto i{ 0u }; i < kHasOnlyFloatComponentCount; ++i) {
            mRegistry.CreateEntity()
                .AssignComponent<TestComponent2>();
        }

        for( auto i{ 0u }; i < kHasBothComponentsCount; ++i) {
            auto entity = mRegistry.CreateEntity();
            entity.AssignComponent<TestComponent1>();
            entity.AssignComponent<TestComponent2>();
        }
    }
};

class PredicatesTests : public RegistryWithEntitiesTests
{
protected:
    uint mCallCounter{ 0u };

    using IncrementCounter = std::function<void(ol::Entity)>;
    IncrementCounter mIncrementCounter = [&c = mCallCounter] (auto) { ++c; };
};

TEST_F(RegistryTests, EntityCount_ZeroByDefault)
{
    ASSERT_EQ(mRegistry.EntityCount(), 0);
}

TEST_F(RegistryTests, EntityCount_IncreasedByCreateEntity)
{
    constexpr auto count{ 10u };

    for (auto i{ 0u }; i < count; ++i) {
        mRegistry.CreateEntity();
    }

    ASSERT_EQ(mRegistry.EntityCount(), count);
}

TEST_F(RegistryTests, EntityCount_DecreasedByDestroyEntityById)
{
    constexpr auto count{ 5u };
    std::vector<ol::EntityId> to_destroy;

    for (auto i{ 0u }; i < count * 2; ++i) {
        const auto& entity = mRegistry.CreateEntity();
        if (i < count) {
            to_destroy.push_back(entity.GetId());
        }
    }

    auto created_entities_count = mRegistry.EntityCount();

    for (auto&& id : to_destroy) {
        mRegistry.DestroyEntity(id);
    }

    EXPECT_EQ(created_entities_count, count * 2);
    ASSERT_EQ(mRegistry.EntityCount(), count);
}

TEST_F(RegistryTests, EntityCount_DecreasedByDestroyEntity)
{
    constexpr auto count{ 10u };

    for (auto i{ 0u }; i < count; ++i) {
        const auto& entity = mRegistry.CreateEntity();
        mRegistry.DestroyEntity(entity);
    }

    ASSERT_EQ(mRegistry.EntityCount(), 0);
}

TEST_F(RegistryTests, EntityCount_IsEntityValid)
{
    constexpr auto count{ 10u };
    bool all_entities_valid{ true };

    for (auto i{ 0u }; i < count; ++i) {
        const auto& entity = mRegistry.CreateEntity();
        if (!mRegistry.IsEntityValid(entity)) {
            all_entities_valid = false;
        }
    }

    ASSERT_TRUE(all_entities_valid);
}

TEST_F(RegistryTests, EntityCount_IsEntityValidById)
{
    constexpr auto count{ 10u };
    bool all_entities_valid{ true };

    for (auto i{ 0u }; i < count; ++i) {
        const auto& entity = mRegistry.CreateEntity();
        if (!mRegistry.IsEntityValid(entity.GetId())) {
            all_entities_valid = false;
        }
    }

    ASSERT_TRUE(all_entities_valid);
}

TEST_F(RegistryTests, CreateEntity_UniqueIds)
{
    constexpr auto entity_count{ 10u };
    auto ids = std::unordered_set<ol::EntityId>{};

    for (auto i{ 0u }; i < entity_count; ++i) {
        const auto id = mRegistry.CreateEntity().GetId();
        ids.insert(id);
    }

    ASSERT_EQ(ids.size(), entity_count);
}

TEST_F(RegistryTests, GetFeature_ThrowsWhenNotFound)
{
    ASSERT_ANY_THROW(mRegistry.GetFeature<TestFeature>());
}

TEST_F(RegistryTests, GetFeatureConst_ThrowsWhenNotFound)
{
    ASSERT_ANY_THROW(std::as_const(mRegistry).GetFeature<TestFeature>());
}

TEST_F(RegistryTests, GetFeature_ReturnsAssignedFeature)
{
    mRegistry.AssignFeature<TestFeature>();

    ASSERT_TRUE(mRegistry.GetFeature<TestFeature>().IsEnabled());
}

TEST_F(RegistryTests, GetOrCreateFeature_ReturnsAssignedFeature)
{
    mRegistry.GetOrCreateFeature<TestFeature>();

    ASSERT_TRUE(mRegistry.GetFeature<TestFeature>().IsEnabled());
}

TEST_F(RegistryTests, GetOrCreateFeature_DoesNotReassign)
{
    mRegistry.AssignFeature<TestFeature>();
    mRegistry.GetFeature<TestFeature>().Disable();
    auto feature = mRegistry.GetOrCreateFeature<TestFeature>();

    ASSERT_TRUE(feature.IsDisabled());
}

TEST_F(RegistryTests, HandleEvent)
{
    bool flag{ false };
    mRegistry.AssignFeature<TestFeature>()
        .AddSystem<TestSystem>(flag);

    mRegistry.HandleEvent(TestEvent{}); // Raises flag

    ASSERT_TRUE(flag);
}

TEST_F(RegistryWithEntitiesTests, ForEachEntity_CountAllEntities)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::Entity) { ++counter; };

    mRegistry.ForEachEntity(callback);

    ASSERT_EQ(counter, mRegistry.EntityCount());
}

TEST_F(PredicatesTests, Exists_CountEntitiesThatHaveComponent)
{
    mRegistry.ForEachEntity(mIncrementCounter,
                            ol::option::Exists<TestComponent1>{});

    ASSERT_EQ(mCallCounter, kHasOnlyBoolComponentCount + kHasBothComponentsCount);
}

TEST_F(PredicatesTests, ExistsAny_CountEntitiesThatHaveEitherComponent)
{
    constexpr auto expected_call_count = kHasOnlyBoolComponentCount
                                         + kHasOnlyFloatComponentCount
                                         + kHasBothComponentsCount;

    auto has_any = ol::option::ExistsAny<TestComponent1, TestComponent2>{};
    mRegistry.ForEachEntity(mIncrementCounter, has_any);

    ASSERT_EQ(mCallCounter, expected_call_count);
}

TEST_F(PredicatesTests, Or_CountEntitesThatHaveEitherComponent)
{
    constexpr auto expected_call_count = kHasOnlyBoolComponentCount
                                         + kHasOnlyFloatComponentCount
                                         + kHasBothComponentsCount;

    auto bool_or_float = ol::option::Or<ol::option::Exists<TestComponent1>,
                                        ol::option::Exists<TestComponent2>>();
    mRegistry.ForEachEntity(mIncrementCounter, bool_or_float);

    ASSERT_EQ(mCallCounter, expected_call_count);
}

TEST_F(PredicatesTests, ExistsAll_CountEntitiesThatHaveBothComponents)
{
    auto predicate = ol::option::ExistsAll<TestComponent1, TestComponent2>{};
    mRegistry.ForEachEntity(mIncrementCounter, predicate);

    ASSERT_EQ(mCallCounter, kHasBothComponentsCount);
}

TEST_F(PredicatesTests, And_CountEntitiesThatHaveBothComponents)
{
    auto bool_and_float = ol::option::And<ol::option::Exists<TestComponent1>,
                                          ol::option::Exists<TestComponent2>>();
    mRegistry.ForEachEntity(mIncrementCounter, bool_and_float);

    ASSERT_EQ(mCallCounter, kHasBothComponentsCount);
}

TEST_F(PredicatesTests, Negate_CountEntitiesThatHaveNoBoolComponent)
{
    auto has_no_bool = ol::option::Negate<ol::option::Exists<TestComponent1>>();
    mRegistry.ForEachEntity(mIncrementCounter, has_no_bool);

    ASSERT_EQ(mCallCounter, kHasNoComponentsCount + kHasOnlyFloatComponentCount);
}

TEST_F(PredicatesTests, Negate_CountEntitiesThatHaveNoComponents)
{
    auto bool_or_float = ol::option::Or<ol::option::Exists<TestComponent1>,
                                        ol::option::Exists<TestComponent2>>();
    auto no_bool_no_float = ol::option::Negate(bool_or_float);
    mRegistry.ForEachEntity(mIncrementCounter, no_bool_no_float);

    ASSERT_EQ(mCallCounter, kHasNoComponentsCount);
}

TEST_F(PredicatesTests, Bool_CountAllEntities)
{
    auto all = ol::option::Bool{ true };
    mRegistry.ForEachEntity(mIncrementCounter, all);

    ASSERT_EQ(mCallCounter, mRegistry.EntityCount());
}

TEST_F(PredicatesTests, Bool_ConditionIsNeverMet)
{
    auto none = ol::option::Bool{ false };
    mRegistry.ForEachEntity(mIncrementCounter, none);

    ASSERT_EQ(mCallCounter, 0u);
}

TEST_F(PredicatesTests, NegateBool_CountAllEntities)
{
    auto none = ol::option::Bool{ false };
    auto all = ol::option::Negate(none);
    mRegistry.ForEachEntity(mIncrementCounter, all);

    ASSERT_EQ(mCallCounter, mRegistry.EntityCount());
}

TEST_F(PredicatesTests, BoolAnd_CountEntitiesThatHaveBoolComponent)
{
    auto bool_pred = ol::option::Bool{ true };
    auto has_bool = ol::option::And(bool_pred,
                                    ol::option::Exists<TestComponent1>{});
    mRegistry.ForEachEntity(mIncrementCounter, has_bool);

    ASSERT_EQ(mCallCounter, kHasOnlyBoolComponentCount + kHasBothComponentsCount);
}

TEST_F(PredicatesTests, BoolAnd_ConditionIsNeverMet)
{
    auto bool_pred = ol::option::Bool{ false };
    auto none = ol::option::And(bool_pred,
                                ol::option::Exists<TestComponent1>{});
    mRegistry.ForEachEntity(mIncrementCounter, none);

    ASSERT_EQ(mCallCounter, 0u);
}

TEST_F(PredicatesTests, BoolOr_CountAllEntities)
{
    auto bool_pred = ol::option::Bool{ true };
    auto all = ol::option::Or(bool_pred,
                              ol::option::Exists<TestComponent1>{});
    mRegistry.ForEachEntity(mIncrementCounter, all);

    ASSERT_EQ(mCallCounter, mRegistry.EntityCount());
}

TEST_F(PredicatesTests, BoolOr_CountEntitiesThatHaveBoolComponent)
{
    auto bool_pred = ol::option::Bool{ false };
    auto all = ol::option::Or(bool_pred,
                              ol::option::Exists<TestComponent1>{});
    mRegistry.ForEachEntity(mIncrementCounter, all);

    ASSERT_EQ(mCallCounter, kHasOnlyBoolComponentCount + kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests, ForEachEntityConst_CountAllEntities)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::ConstEntity) { ++counter; };

    std::as_const(mRegistry).ForEachEntity(callback);

    ASSERT_EQ(counter, mRegistry.EntityCount());
}

TEST_F(RegistryWithEntitiesTests,
       ForEachEntityConst_Predicates_CountEntitiesThatHaveBothComponents)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::ConstEntity) { ++counter; };

    auto bool_and_float = ol::option::ExistsAll<TestComponent1,
                                                TestComponent2>{};
    std::as_const(mRegistry).ForEachEntity(callback, bool_and_float);

    ASSERT_EQ(counter, kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForEachComponent_CountEntitiesThatHaveComponent)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::Entity, TestComponent1&) { ++counter; };

    mRegistry.ForEachComponent<TestComponent1>(callback);

    ASSERT_EQ(counter, kHasOnlyBoolComponentCount + kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForEachComponent_Predicates_CountEntitiesThatHaveBothComponents)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::Entity, TestComponent1&) { ++counter; };

    auto has_float = ol::option::Exists<TestComponent2>{};
    mRegistry.ForEachComponent<TestComponent1>(callback, has_float);

    ASSERT_EQ(counter, kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForEachComponentConst_CountEntitiesThatHaveComponent)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::ConstEntity, const TestComponent1&)
    { ++counter; };

    std::as_const(mRegistry).ForEachComponent<TestComponent1>(callback);

    ASSERT_EQ(counter, kHasOnlyBoolComponentCount + kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForEachComponentConst_Predicates_CountEntitiesThatHaveBothComponents)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::ConstEntity, const TestComponent1&)
    { ++counter; };

    auto has_float = ol::option::Exists<TestComponent2>{};
    std::as_const(mRegistry).ForEachComponent<TestComponent1>(callback,
                                                              has_float);

    ASSERT_EQ(counter, kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForEachComponent_Multiple_CountEntitiesThatHaveComponent)
{
    auto counter_bool{ 0u };
    auto counter_float{ 0u };
    auto inc_bool = [&c = counter_bool] (ol::Entity, TestComponent1&) { ++c; };
    auto inc_float = [&c = counter_float] (ol::Entity, TestComponent2&) { ++c; };

    mRegistry.ForEachComponent<TestComponent1>(inc_bool);
    mRegistry.ForEachComponent<TestComponent2>(inc_float);

    EXPECT_EQ(counter_bool,
              kHasOnlyBoolComponentCount + kHasBothComponentsCount);
    ASSERT_EQ(counter_float,
              kHasOnlyFloatComponentCount + kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForEachComponentConst_Multiple_CountEntitiesThatHaveComponent)
{
    auto counter_bool{ 0u };
    auto counter_float{ 0u };
    auto inc_bool = [&c = counter_bool] (ol::Entity, TestComponent1&) { ++c; };
    auto inc_float = [&c = counter_float] (ol::Entity, TestComponent2&) { ++c; };

    mRegistry.ForEachComponent<TestComponent1>(inc_bool);
    mRegistry.ForEachComponent<TestComponent2>(inc_float);

    EXPECT_EQ(counter_bool,
              kHasOnlyBoolComponentCount + kHasBothComponentsCount);
    ASSERT_EQ(counter_float,
              kHasOnlyFloatComponentCount + kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests, ForEachComponent_ModifiesEachComponent)
{
    auto counter{ 0u };
    auto modify = [] (ol::Entity, TestComponent1& component)
    {
        component.flag = true;
    };
    auto modified_test = [&counter] (ol::Entity, const TestComponent1& component)
    {
        if (component.flag) {
            ++counter;
        }
    };

    mRegistry.ForEachComponent<TestComponent1>(modify);
    mRegistry.ForEachComponent<TestComponent1>(modified_test);

    ASSERT_EQ(counter, kHasOnlyBoolComponentCount + kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForJoinedComponents_CountAllEntitiesThatHaveJoinedComponents)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::Entity, TestComponent1&, TestComponent2&)
    { ++counter; };

    mRegistry.ForJoinedComponents<TestComponent1, TestComponent2>(callback);

    ASSERT_EQ(counter, kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForJoinedComponents_Predicates_CountAllEntitiesThatHaveJoinedComponents)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::Entity, TestComponent1&, TestComponent2&)
    { ++counter; };

    auto pred_true = ol::option::Bool{ true };
    mRegistry.ForJoinedComponents<TestComponent1, TestComponent2>(callback,
                                                                  pred_true);

    ASSERT_EQ(counter, kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForJoinedComponents_Predicates_ConditionIsNeverMet)
{
    auto counter{ 0u };
    auto callback = [&counter] (ol::Entity, TestComponent1&, TestComponent2&)
    { ++counter; };

    auto pred_false = ol::option::Bool{ false };
    mRegistry.ForJoinedComponents<TestComponent1, TestComponent2>(callback,
                                                                  pred_false);

    ASSERT_EQ(counter, 0u);
}

TEST_F(RegistryWithEntitiesTests,
       ForJoinedComponents_ModifiesEachEntityWithComponentCombination)
{
    constexpr auto xvalue{ 5.f };
    constexpr auto yvalue{ 9.f };
    auto counter{ 0u };
    auto modify = [] (ol::Entity, TestComponent1& c1, TestComponent2& c2)
    {
        c1.flag = true;
        c2.x = xvalue;
        c2.y = yvalue;
    };
    auto modified_test = [&counter]
    (ol::Entity, const TestComponent1& c1, const TestComponent2& c2)
    {
        const auto x_equals = !std::islessgreater(c2.x, xvalue);
        const auto y_equals = !std::islessgreater(c2.y, yvalue);
        if (c1.flag && x_equals && y_equals) {
            ++counter;
        }
    };

    mRegistry.ForJoinedComponents<TestComponent1, TestComponent2>(modify);
    mRegistry.ForJoinedComponents<TestComponent1, TestComponent2>(modified_test);

    ASSERT_EQ(counter, kHasBothComponentsCount);
}

TEST_F(RegistryWithEntitiesTests,
       ForJoinedComponentsConst_CalledForEachEntityWithComponentCombination)
{
    auto counter{ 0u };
    auto callback = [&counter]
    (ol::ConstEntity, const TestComponent1&, const TestComponent2&)
    { ++counter; };

    const auto& registry = std::as_const(mRegistry);
    registry.ForJoinedComponents<TestComponent1, TestComponent2>(callback);

    ASSERT_EQ(counter, kHasBothComponentsCount);
}

} // namespace test

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
