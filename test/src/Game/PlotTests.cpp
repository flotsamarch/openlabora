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
#include <gmock/gmock.h>
#include "Game/Plot.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"

namespace test
{

namespace ol = open_labora;

using PlotTests = ResourceManagerDefaultActionTestBase;

using testing::Return;
using testing::ReturnRef;
using testing::StrEq;
using testing::_;
using RMM = IResourceManagerMock;

TEST_F(PlotTests, Create_TextureNotRegistered)
{
    auto&& id = ol::plot::kTextureIdMap.Get(ol::plot::Type::Coastal)[0];

    EXPECT_CALL(*mResourceMgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{}));

    EXPECT_CALL(*mResourceMgr, GetTextureOrDefault)
        .WillRepeatedly(ReturnRef(mTexture));

    EXPECT_CALL(*mResourceMgr, RegisterTexture(StrEq(id), _))
        .WillOnce(ReturnRef(mTexture));

    auto plot = ol::plot::create(ol::plot::Type::Coastal,
                                 sf::Vector2f{},
                                 mResourceMgr);
}

TEST_F(PlotTests, Create_TextureIsRegistered)
{
    auto&& id = ol::plot::kTextureIdMap.Get(ol::plot::Type::Coastal)[0];
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*mResourceMgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{ texture }));

    EXPECT_CALL(*mResourceMgr, GetTextureOrDefault)
        .Times(0);

    EXPECT_CALL(*mResourceMgr, RegisterTexture)
        .Times(0);

    auto plot = ol::plot::create(ol::plot::Type::Coastal,
                                 sf::Vector2f{},
                                 mResourceMgr);
}

TEST_F(PlotTests, CreateCentralInitial_TextureNotRegistered)
{
    auto&& id = ol::plot::kCentralInitAltTextureName;

    EXPECT_CALL(*mResourceMgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{}));

    EXPECT_CALL(*mResourceMgr, GetTextureOrDefault)
        .WillRepeatedly(ReturnRef(mTexture));

    EXPECT_CALL(*mResourceMgr, RegisterTexture(StrEq(id), _))
        .WillOnce(ReturnRef(mTexture));

    auto plot = ol::plot::createCentralInitial(sf::Vector2f{},
                                               mResourceMgr,
                                               true);
}

TEST_F(PlotTests, CreateCentralInitial_TextureIsRegistered)
{
    auto&& id = ol::plot::kCentralInitAltTextureName;

    EXPECT_CALL(*mResourceMgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{ mTexture }));

    EXPECT_CALL(*mResourceMgr, GetTextureOrDefault)
        .Times(0);

    EXPECT_CALL(*mResourceMgr, RegisterTexture)
        .Times(0);

    auto plot = ol::plot::createCentralInitial(sf::Vector2f{},
                                               mResourceMgr,
                                               true);
}

TEST_F(PlotTests, SetPosition)
{
    constexpr auto x = 932.5723f;
    constexpr auto y = 894.3002f;
    auto plot = ol::plot::create(ol::plot::Type::Begin,
                                 sf::Vector2f{},
                                 mResourceMgr);
    auto&& position_cmpnt = ol::ecs::getComponent<ol::PositionComponent>(plot);
    auto&& sprite_cmpnt = ol::ecs::getComponent<ol::SpriteComponent>(plot);

    ol::plot::setPosition(plot, {x, y});

    EXPECT_FLOAT_EQ(position_cmpnt.position.x, x);
    EXPECT_FLOAT_EQ(position_cmpnt.position.y, y);
    EXPECT_FLOAT_EQ(sprite_cmpnt.GetPosition().x, x);
    ASSERT_FLOAT_EQ(sprite_cmpnt.GetPosition().y, y);
}

TEST_F(PlotTests, SetPosition_ShiftCentral)
{
    constexpr auto x = 932.5723f;
    constexpr auto y = 894.3002f;
    auto plot = ol::plot::create(ol::plot::Type::Central,
                                 sf::Vector2f{},
                                 mResourceMgr);
    auto&& position_cmpnt = ol::ecs::getComponent<ol::PositionComponent>(plot);
    auto&& sprite_cmpnt = ol::ecs::getComponent<ol::SpriteComponent>(plot);

    ol::plot::setPosition(plot, {x, y}, true);

    EXPECT_FLOAT_EQ(position_cmpnt.position.x, x);
    EXPECT_FLOAT_EQ(position_cmpnt.position.y, y);
    EXPECT_FLOAT_EQ(sprite_cmpnt.GetPosition().x, x);
    ASSERT_FLOAT_EQ(sprite_cmpnt.GetPosition().y, y);
}

TEST_F(PlotTests, SetPosition_ShiftNonCetral)
{
    constexpr auto x = 932.5723f;
    constexpr auto y = 894.3002f;
    constexpr auto tile_h = ol::tile::kTileHeight;
    auto plot = ol::plot::create(ol::plot::Type::Begin,
                                 sf::Vector2f{},
                                 mResourceMgr);
    auto&& position_cmpnt = ol::ecs::getComponent<ol::PositionComponent>(plot);
    auto&& sprite_cmpnt = ol::ecs::getComponent<ol::SpriteComponent>(plot);

    ol::plot::setPosition(plot, {x, y}, true);
    EXPECT_FLOAT_EQ(position_cmpnt.position.x, x);
    EXPECT_FLOAT_EQ(position_cmpnt.position.y, y + tile_h);
    EXPECT_FLOAT_EQ(sprite_cmpnt.GetPosition().x, x);
    ASSERT_FLOAT_EQ(sprite_cmpnt.GetPosition().y, y + tile_h);
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
