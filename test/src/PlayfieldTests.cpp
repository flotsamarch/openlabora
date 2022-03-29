#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Resource/IResourceManagerMock.hpp"
#include "game/Playfield.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Test
{

using ::testing::NiceMock;
using ::testing::ReturnRef;
using ::testing::_;

#if 0
class TFPlayfieldTests : public ::testing::Test
{
protected:
    NiceMock<ResourceManagerMock> mResMgr;
    sf::Texture mTexture;
    unsigned int fw = Playfield::kFieldWidth;
    unsigned int tw = Playfield::kTileWidth;
    unsigned int th = Playfield::kTileHeight;

    sf::Vector2f oob{ fw * tw + 5.f, 0.0f }; // out of bounds
    sf::Vector2f point1{ 0.5f, 0.5f };
    sf::Vector2f point2{ 10.5f + tw, 10.5f + th };
    sf::Vector2f point3{ 70.5f + 8 * tw, 24.5f + 4 * th };

};

TEST_F(TFPlayfieldTests, RequestsTextures)
{
    EXPECT_CALL(mResMgr, GetTextureByName(_))
        .Times(6)
        .WillRepeatedly(ReturnRef(mTexture));

    Playfield mPf{ mResMgr };
}

TEST_F(TFPlayfieldTests, Snapping)
{
    EXPECT_CALL(mResMgr, GetTextureByName(_))
        .WillRepeatedly(ReturnRef(mTexture));

    Playfield mPf{ mResMgr };

    auto resoob = mPf.SnapPointToTile(oob);
    auto res1 = mPf.SnapPointToTile(point1);
    auto res2 = mPf.SnapPointToTile(point2);
    auto res3 = mPf.SnapPointToTile(point3);

    EXPECT_EQ(resoob, GameObject::kOutOfBounds);
    EXPECT_EQ(res1, sf::Vector2f(0.f, 0.f));
    EXPECT_EQ(res2, sf::Vector2f(tw, th));
    EXPECT_EQ(res3, sf::Vector2f(8 * tw, 4 * th));
}

TEST_F(TFPlayfieldTests, FindLocationOnTileGrid)
{
    EXPECT_CALL(mResMgr, GetTextureByName(_))
        .WillRepeatedly(ReturnRef(mTexture));

    Playfield mPf{ mResMgr };

    auto res1 = mPf.SnapPointToTile(point1);
    auto res2 = mPf.SnapPointToTile(point2);
    auto res3 = mPf.SnapPointToTile(point3);

    auto locoob = mPf.GetLocationUnderPoint(oob);
    auto&& loc1 = *mPf.GetLocationUnderPoint(point1);
    auto&& loc2 = *mPf.GetLocationUnderPoint(point2);
    auto&& loc3 = *mPf.GetLocationUnderPoint(point3);

    EXPECT_EQ(loc1->GetSprite().getPosition(), res1);
    EXPECT_EQ(loc2->GetSprite().getPosition(), res2);
    EXPECT_EQ(loc3->GetSprite().getPosition(), res3);
    ASSERT_EQ(locoob, mPf.LocationsEnd());
}

TEST_F(TFPlayfieldTests, LocationCreation)
{
    EXPECT_CALL(mResMgr, GetTextureByName(_))
        .WillRepeatedly(ReturnRef(mTexture));

    Playfield mPf{ mResMgr };

    auto loctype1 = (*mPf.GetLocationUnderPoint(point1))->GetType();
    auto loctype2 = (*mPf.GetLocationUnderPoint(point2))->GetType();
    auto loctype3 = (*mPf.GetLocationUnderPoint(point3))->GetType();

    // Should be created
    mPf.ChangeLocationTypeAtPoint(point1, Location::LocationType::HouseBoat);
    mPf.ChangeLocationTypeAtPoint(point2,
                                  Location::LocationType::FishingVillage);
    // Shouldn't be created
    mPf.ChangeLocationTypeAtPoint(point3, Location::LocationType::Peat);
    EXPECT_NO_FATAL_FAILURE( \
        mPf.ChangeLocationTypeAtPoint(oob, Location::LocationType::Forest));

    auto&& loc1 = *mPf.GetLocationUnderPoint(point1);
    auto&& loc2 = *mPf.GetLocationUnderPoint(point2);
    auto&& loc3 = *mPf.GetLocationUnderPoint(point3);


    EXPECT_NE(loc1->GetType(), loctype1);
    EXPECT_NE(loc2->GetType(), loctype2);
    ASSERT_EQ(loc3->GetType(), loctype3);
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
