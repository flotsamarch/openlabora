#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Game/Tile.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace Test
{

using OpenLabora::Tile;
using Type = Tile::TileType;
using ::testing::ReturnRef;

class TestFTile : public ::testing::Test
{
protected:
    IResourceManagerMock::Ptr mResManager =
        std::make_shared<IResourceManagerMock>();

    sf::Texture mTexture;
public:
    TestFTile() { mTexture.create(1u, 1u); }
    virtual ~TestFTile() {};
};

TEST_F(TestFTile, IsValid)
{
    EXPECT_CALL(*mResManager, GetTextureByName)
        .WillOnce(ReturnRef(mTexture));

    auto invalid_tile = Tile{ Type::None, mResManager };
    auto tile = Tile{ Type::Begin + 1, mResManager }; // First non-None

    EXPECT_FALSE(invalid_tile.IsValid());
    ASSERT_TRUE(tile.IsValid());
}

TEST_F(TestFTile, Construction)
{
    for (auto type = Type::Begin; type < Type::End; ++type) {
        if (type != Type::None) {
            EXPECT_CALL(*mResManager, GetTextureByName)
                .WillOnce(ReturnRef(mTexture))
                .RetiresOnSaturation();
        }

        auto tile{ Tile{ type, mResManager } };
        if (type != Type::None) {
            EXPECT_TRUE(tile.IsValid());
        }
    }
}

TEST_F(TestFTile, TileInfo)
{
    constexpr float position{ 150.f };
    constexpr float offset{ 10.f };

    EXPECT_CALL(*mResManager, GetTextureByName)
        .WillOnce(ReturnRef(mTexture));

    auto tile = Tile{ Type::Begin + 1, mResManager }; // First non-None

    auto info = tile.GetTileInfo();

    auto default_info = Tile::TileInfo{};

    EXPECT_NE(info, default_info);

    tile.SetPosition(position, position);
    info = tile.GetTileInfo();

    EXPECT_EQ(info.coord.x, position);
    EXPECT_EQ(info.coord.y, position);

    tile.Move(offset, offset);
    info = tile.GetTileInfo();

    EXPECT_EQ(info.coord.x, position + offset);
    ASSERT_EQ(info.coord.y, position + offset);
}

TEST(TileOperatorsTests, OperatorPlus)
{
    constexpr auto begin = static_cast<int>(Type::Begin);
    constexpr auto forest_offset = static_cast<int>(Type::Forest) - begin;
    constexpr auto peat_offset = static_cast<int>(Type::Peat) - begin;
    constexpr auto very_big_number = static_cast<int>(Type::End) + 999999;

    EXPECT_EQ(Type::Begin + forest_offset, Type::Forest);
    EXPECT_EQ(Type::Begin + peat_offset, Type::Peat);
    EXPECT_EQ(Type::Begin + very_big_number, Type::End);
    EXPECT_EQ(forest_offset + Type::Begin, Type::Forest);
    EXPECT_EQ(peat_offset + Type::Begin, Type::Peat);
    ASSERT_EQ(very_big_number + Type::Begin, Type::End);
}

TEST(TileOperatorsTests, OperatorPreincrement)
{
    constexpr auto begin = static_cast<size_t>(Type::Begin);
    constexpr auto end = static_cast<size_t>(Type::End);
    constexpr auto delta = end - begin;
    auto type = Type::Begin;

    for (size_t i{ 0 }; i < delta; ++i, ++type) {};

    ASSERT_EQ(type, Type::End);
}

TEST(TileOperatorsTests, TileInfoOperatorEquals)
{
    Tile::TileInfo one, two;

    EXPECT_TRUE(one == two);

    one.valid = true;

    EXPECT_FALSE(one == two);

    two.valid = true;

    EXPECT_TRUE(one == two);

    one.type = Type::Begin + 1;

    EXPECT_FALSE(one == two);

    two.type = Type::Begin + 1;

    EXPECT_TRUE(one == two);

    one.coord.x = 1.5f;

    EXPECT_FALSE(one == two);

    two.coord.x = 1.5f;

    EXPECT_TRUE(one == two);

    one.coord.y = 5.52345234f;

    EXPECT_FALSE(one == two);

    two.coord.y = 5.52345234f;

    ASSERT_TRUE(one == two);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
