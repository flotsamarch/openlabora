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

#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Resource/IResourceManagerMock.hpp"
#include "game/Location.hpp"

namespace Test
{

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::_;
#if 0
class TFLocationTests : public ::testing::Test
{
protected:
    NiceMock<ResourceManagerMock> mResMgr;
    sf::Texture mTexture;

public:
    TFLocationTests() {
    }
};

TEST_F(TFLocationTests, AccessesTexture)
{
    EXPECT_CALL(mResMgr, GetTextureByName(_))
        .Times(1)
        .WillRepeatedly(ReturnRef(mTexture));

   ASSERT_NO_FATAL_FAILURE( \
       Location location(mResMgr, Location::LocationType::Empty) \
       );
}

TEST_F(TFLocationTests, LocationType)
{
    EXPECT_CALL(mResMgr, GetTextureByName(_))
        .WillRepeatedly(ReturnRef(mTexture));

    Location location{ mResMgr, Location::LocationType::Empty };
    Location location2{ mResMgr, Location::LocationType::Forest };

    EXPECT_EQ(location.GetType(), Location::LocationType::Empty);
    ASSERT_EQ(location2.GetType(), Location::LocationType::Forest);
}

// TODO iterate somehow over LocationType enum to check correctness
TEST_F(TFLocationTests, Placeable)
{
    EXPECT_CALL(mResMgr, GetTextureByName(_))
        .WillRepeatedly(ReturnRef(mTexture));

    Location location{ mResMgr, Location::LocationType::Empty };
    Location location2{ mResMgr, Location::LocationType::Forest };

    ASSERT_FALSE(location.IsPlaceableOn(location.GetType(),
                                        Tile::TileType::Forest));
    ASSERT_TRUE(location.IsPlaceableOn(location2.GetType(),
                                        Tile::TileType::Forest));
}
#endif
}
#if 0
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
