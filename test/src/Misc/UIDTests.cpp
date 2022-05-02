#include <gtest/gtest.h>
#include "Misc/UID.hpp"

namespace Test
{

using OpenLabora::uid::getUid;

TEST(UidTests, GetUid)
{
    for (int i = 0; i < 50; ++i)
    {
        EXPECT_EQ(i, getUid());
    }
}

#if 0 // TODO: Add this test if at any moment some sort of id setter is available
TEST(UidTests, GetOverMaxThrows)
{
    constexpr auto max = std::numeric_limits<uint64_t>::max();
    for (uint64_t i = 0; i <= max; ++i) {
        getUid();
    }

    EXPECT_THROW(getUid(), std::overflow_error);
}
#endif

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
