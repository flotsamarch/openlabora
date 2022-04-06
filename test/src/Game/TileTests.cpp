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

class TileTests: public ::testing::Test
{
protected:
    IResourceManagerMock::Ptr mResManager =
        std::make_shared<IResourceManagerMock>();

    sf::Texture mTexture;
public:
    virtual ~TileTests() {};

    TileTests()
    {
        mTexture.create(1u, 1u);

        ON_CALL(*mResManager, GetTextureByName)
            .WillByDefault(ReturnRef(mTexture));
    }
};

TEST_F(TileTests, IsValid)
{
    EXPECT_CALL(*mResManager, GetTextureByName)
        .Times(1);

    auto invalid_tile = Tile{ Type::None, mResManager };
    auto tile = Tile{ Type::Begin + 1, mResManager }; // First non-None

    EXPECT_FALSE(invalid_tile.IsValid());
    ASSERT_TRUE(tile.IsValid());
}

TEST_F(TileTests, Construction)
{
    for (auto type = Type::Begin; type < Type::End; ++type) {
        if (type != Type::None) {
            EXPECT_CALL(*mResManager, GetTextureByName)
                .Times(1)
                .RetiresOnSaturation();
        }

        auto tile{ Tile{ type, mResManager } };
        if (type != Type::None) {
            EXPECT_TRUE(tile.IsValid());
        }
    }
}

TEST_F(TileTests, TileInfo)
{
    constexpr float position{ 150.f };
    constexpr float offset{ 10.f };

    auto tile = Tile{ Type::Begin + 1, mResManager }; // First non-None

    auto info = tile.GetTileInfo();

    auto default_info = Tile::TileInfo{};

    EXPECT_NE(info, default_info);

    tile.Move(offset, offset);
    info = tile.GetTileInfo();
    EXPECT_EQ(info.coord.x, offset);
    EXPECT_EQ(info.coord.y, offset);

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

TEST_F(TileTests, EntityTransformations)
{
    constexpr auto offset_x = 10.4f;
    constexpr auto offset_y = 11.4f;
    constexpr auto position_x = 150.15f;
    constexpr auto position_y = 152.15f;
    auto tile_1 = Tile{ Type::Begin + 1, mResManager };
    auto tile_2 = Tile{ Type::Begin + 1, mResManager };

    ASSERT_FLOAT_EQ(tile_1.GetPosition().x, 0.f);
    ASSERT_FLOAT_EQ(tile_1.GetPosition().y, 0.f);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().x, 0.f);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().y, 0.f);

    tile_1.Move(offset_x, offset_y);
    tile_2.Move(sf::Vector2f{ offset_x, offset_y });

    ASSERT_FLOAT_EQ(tile_1.GetPosition().x, offset_x);
    ASSERT_FLOAT_EQ(tile_1.GetPosition().y, offset_y);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().x, offset_x);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().y, offset_y);

    tile_1.SetPosition(position_x, position_y);
    tile_2.SetPosition(sf::Vector2f{ position_x, position_y });

    ASSERT_FLOAT_EQ(tile_1.GetPosition().x, position_x);
    ASSERT_FLOAT_EQ(tile_1.GetPosition().y, position_y);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().x, position_x);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().y, position_y);

    tile_1.Move(offset_x, offset_y);
    tile_2.Move(sf::Vector2f{ offset_x, offset_y });

    ASSERT_FLOAT_EQ(tile_1.GetPosition().x, offset_x + position_x);
    ASSERT_FLOAT_EQ(tile_1.GetPosition().y, offset_y + position_y);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().x, offset_x + position_x);
    ASSERT_FLOAT_EQ(tile_2.GetPosition().y, offset_y + position_y);
}

TEST_F(TileTests, GetDrawableObject)
{
    auto tile = Tile{ Type::Begin + 1, mResManager };

    auto&& drawable = tile.GetDrawableObject();
    ASSERT_EQ(static_cast<const sf::Sprite&>(drawable).getTexture(), &mTexture);
}

TEST_F(TileTests, EntityBounds)
{
    constexpr auto offset_x = 10.4f;
    constexpr auto offset_y = 11.4f;
    auto tile = Tile{ Type::Begin + 1, mResManager };

    auto bounds = tile.GetLocalBounds();
    EXPECT_EQ(bounds.width, OpenLabora::Tile::kTileWidth);
    EXPECT_EQ(bounds.height, OpenLabora::Tile::kTileHeight);
    ASSERT_EQ(bounds, tile.GetGlobalBounds());

    tile.Move(offset_x, offset_y);
    bounds = tile.GetGlobalBounds();
    EXPECT_EQ(bounds.width, OpenLabora::Tile::kTileWidth);
    EXPECT_EQ(bounds.height, OpenLabora::Tile::kTileHeight);
    EXPECT_EQ(bounds.left, offset_x);
    ASSERT_EQ(bounds.top, offset_y);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
