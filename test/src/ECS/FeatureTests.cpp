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
#include "ECS/Feature.hpp"

namespace test
{

namespace ol = open_labora;

class FeatureTests : public testing::Test
{
    ecs_hpp::feature mLibFeature{};
protected:
    ol::Feature mFeature{ mLibFeature };
};

class ConstFeatureTests : public testing::Test
{
protected:
    ecs_hpp::feature mLibFeature{};
    ol::ConstFeature mFeature{ mLibFeature };
};

TEST_F(FeatureTests, IsDisabledByDefault_False)
{
    ASSERT_FALSE(mFeature.IsDisabled());
}

TEST_F(FeatureTests, IsEnabledByDefault_True)
{
    ASSERT_TRUE(mFeature.IsEnabled());
}

TEST_F(FeatureTests, IsDisabledAfterDisable_True)
{
    mFeature.Disable();
    ASSERT_TRUE(mFeature.IsDisabled());
}

TEST_F(FeatureTests, IsEnabledAfterDisable_False)
{
    mFeature.Disable();
    ASSERT_FALSE(mFeature.IsEnabled());
}

TEST_F(FeatureTests, IsEnabledAfterEnable_True)
{
    mFeature.Disable();
    mFeature.Enable();
    ASSERT_TRUE(mFeature.IsEnabled());
}

TEST_F(FeatureTests, IsDisabledAfterEnable_False)
{
    mFeature.Disable();
    mFeature.Enable();
    ASSERT_FALSE(mFeature.IsDisabled());
}

TEST_F(ConstFeatureTests, IsDisabledByDefault_False)
{
    ASSERT_FALSE(mFeature.IsDisabled());
}

TEST_F(ConstFeatureTests, IsEnabledByDefault_True)
{
    ASSERT_TRUE(mFeature.IsEnabled());
}

TEST_F(ConstFeatureTests, IsDisabledAfterDisable_True)
{
    mLibFeature.disable();
    ASSERT_TRUE(mFeature.IsDisabled());
}

TEST_F(ConstFeatureTests, IsEnabledAfterDisable_False)
{
    mLibFeature.disable();
    ASSERT_FALSE(mFeature.IsEnabled());
}

TEST_F(ConstFeatureTests, IsEnabledAfterEnable_True)
{
    mLibFeature.disable();
    mLibFeature.enable();
    ASSERT_TRUE(mFeature.IsEnabled());
}

TEST_F(ConstFeatureTests, IsDisabledAfterEnable_False)
{
    mLibFeature.disable();
    mLibFeature.enable();
    ASSERT_FALSE(mFeature.IsDisabled());
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
