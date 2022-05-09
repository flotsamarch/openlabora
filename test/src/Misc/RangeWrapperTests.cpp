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
#include <vector>

#include "Misc/RangeWrapper.hpp"

namespace Test
{

using ::OpenLabora::RangeWrapper;

TEST(RangeWrapperTests, EmptyDefaultRange)
{
    auto wrapper = RangeWrapper<std::vector<int>::iterator>{};
    ASSERT_EQ(std::distance(wrapper.begin(), wrapper.end()), 0);
}

TEST(RangeWrapperTests, EmptyNonDefaultRange)
{
    auto vector = std::vector<int>{};
    auto wrapper = RangeWrapper{ vector };
    ASSERT_EQ(std::distance(wrapper.begin(), wrapper.end()), 0);
}

TEST(RangeWrapperTests, NonEmptyRange)
{
    auto vector = std::vector<int>{ 1, 2, 3 };
    auto wrapper = RangeWrapper{ vector };
    ASSERT_NE(std::distance(wrapper.begin(), wrapper.end()), 0);
}

TEST(RangeWrapperTests, RangeBasedForLoopSupport)
{
    auto vector = std::vector<int>{ 0, 1, 2 };
    auto wrapper = RangeWrapper{ vector };

    for (int i = 0; auto&& item : wrapper) {
        EXPECT_EQ(item, i);
        i++;
    }
}

TEST(RangeWrapperTests, IsEmpty_Empty)
{
    auto vector = std::vector<int>{};
    auto wrapper = RangeWrapper{ vector };
    ASSERT_TRUE(wrapper.IsEmpty());
}


TEST(RangeWrapperTests, IsEmpty_NonEmpty)
{
    auto vector = std::vector<int>{ 1, 2, 3 };
    auto wrapper = RangeWrapper{ vector };
    ASSERT_FALSE(wrapper.IsEmpty());
}

TEST(RangeWrapperTests, GetSize_Empty)
{
    auto vector = std::vector<int>{};
    auto wrapper = RangeWrapper{ vector };
    ASSERT_EQ(wrapper.GetSize(), 0);
}

TEST(RangeWrapperTests, GetSize_NonEmpty)
{
    auto vector = std::vector<int>{ 1, 2, 3 };
    auto wrapper = RangeWrapper{ vector };
    ASSERT_EQ(wrapper.GetSize(), 3);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
