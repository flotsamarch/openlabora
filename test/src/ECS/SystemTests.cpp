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
#include "ECS/System.hpp"
#include "ECS/Registry.hpp"

namespace test
{

namespace ol = open_labora;

namespace
{

struct TestEvent1{};
struct TestEvent2{};

struct TestFeature{};

struct TestSystemSingle : public ol::System<TestSystemSingle, TestEvent1>
{
    bool flag{ false };
};

void systemHandleEvent(TestSystemSingle& system, // Used in ol::System<...>
                       ol::RegistryRef,
                       const TestEvent1&)
{
    system.flag = true;
};

struct TestSystemDouble : public ol::System<TestSystemDouble,
                                            TestEvent1,
                                            TestEvent2>
{
    bool flag1{ false };
    bool flag2{ false };
};

void systemHandleEvent(TestSystemDouble& system, // Used in ol::System<...>
                       ol::RegistryRef,
                       const TestEvent1&)
{
    system.flag1 = true;
};

void systemHandleEvent(TestSystemDouble& system, // Used in ol::System<...>
                       ol::RegistryRef,
                       const TestEvent2&)
{
    system.flag2 = true;
};

} // namespace anonymous

TEST(SystemTests, HandleEventSingle)
{
    auto system = TestSystemSingle{};
    auto registry = ecs_hpp::registry{};
    auto reg = ol::RegistryRef{ registry };
    reg.AssignFeature<TestFeature>()
        .AddSystem<TestSystemSingle>();

    auto ptr = ol::PtrView<ecs_hpp::system<TestEvent1>>{ &system };
    ptr->process(registry, TestEvent1{});

    ASSERT_TRUE(system.flag);
}

TEST(SystemTests, HandleEventMultiple)
{

    auto system = TestSystemDouble{};
    auto registry = ecs_hpp::registry{};
    auto reg = ol::RegistryRef{ registry };

    auto ptr1 = ol::PtrView<ecs_hpp::system<TestEvent1>>{ &system };
    ptr1->process(registry, TestEvent1{});

    bool flag2_after_process1 = system.flag2;

    auto ptr2 = ol::PtrView<ecs_hpp::system<TestEvent2>>{ &system };
    ptr2->process(registry, TestEvent2{});

    EXPECT_FALSE(flag2_after_process1);
    EXPECT_TRUE(system.flag1);
    ASSERT_TRUE(system.flag2);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}
