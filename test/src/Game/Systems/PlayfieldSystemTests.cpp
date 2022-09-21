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
#include <sstream>
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "Game/Systems/PlayfieldSystem.hpp"
#include "Game/Components/LotDequeComponent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/DynamicTextureComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"


namespace test
{

namespace ol = open_labora;

using testing::ReturnRef;
using testing::MatchesRegex;
using testing::_;

class PlayfieldSystemTests : public ResourceManagerDefaultActionTestBase
{
protected:
    ol::Registry mRegistry;
    ol::RegistryRef mRegistryRef{ mRegistry };
    ol::PlayfieldSystem mSystem{ mRegistry, mResourceMgr };
};

TEST_F(PlayfieldSystemTests, HasHeartlandByDefault)
{
    auto entity = mSystem.GetLotDeques().at(ol::lot::Type::Central);
    auto&& deque = entity.GetComponent<ol::LotDequeComponent>();

    ASSERT_EQ(deque.GetLotsCount(), 2);
}

TEST_F(PlayfieldSystemTests, HeartlandDefaultPosition)
{
    constexpr auto central = ol::lot::Type::Central;
    const auto offset_x = static_cast<float>(ol::lot::getOffsetX(central));
    const auto offset_y = static_cast<float>(ol::lot::kHeartlandOffsetY);

    auto entity = mSystem.GetLotDeques().at(central);
    auto&& deque = entity.GetComponent<ol::PositionComponent>();

    EXPECT_FLOAT_EQ(deque.x, offset_x);
    ASSERT_FLOAT_EQ(deque.y, offset_y);
}

TEST_F(PlayfieldSystemTests, DynamicTextureNeedsUpdateByDefault)
{
    constexpr auto central = ol::lot::Type::Central;
    auto entity = mSystem.GetLotDeques().at(central);
    auto&& texture = entity.GetComponent<ol::DynamicTextureComponent>();

    ASSERT_TRUE(texture.NeedsUpdate());
}

TEST_F(PlayfieldSystemTests, HandleEvent_CreatePlotEvent_Central_ToTop)
{
    constexpr auto central = ol::lot::Type::Central;
    constexpr auto plot_type = ol::plot::kCentral;

    auto entity = mSystem.GetLotDeques().at(central);
    auto&& deque = entity.GetComponent<ol::LotDequeComponent>();
    auto position_before = entity.GetComponent<ol::PositionComponent>();

    auto plot = ol::plot::getPlots(central)[plot_type];
    auto create_plot_event = ol::CreatePlotEvent{ plot, central, true };

    ol::systemHandleEvent(mSystem, mRegistryRef, create_plot_event);
    auto position_after = entity.GetComponent<ol::PositionComponent>();

    EXPECT_EQ(position_before.x, position_after.x);
    EXPECT_GT(position_before.y, position_after.y);
    ASSERT_EQ(deque.GetLotsCount(), 3);
}

TEST_F(PlayfieldSystemTests, HandleEvent_CreatePlotEvent_Central_ToBottom)
{
    constexpr auto central = ol::lot::Type::Central;
    constexpr auto plot_type = ol::plot::kCentralAlt;

    auto entity = mSystem.GetLotDeques().at(central);
    auto&& deque = entity.GetComponent<ol::LotDequeComponent>();
    auto position_before = entity.GetComponent<ol::PositionComponent>();

    auto plot = ol::plot::getPlots(central)[plot_type];
    auto create_plot_event = ol::CreatePlotEvent{ plot, central, false };

    ol::systemHandleEvent(mSystem, mRegistryRef, create_plot_event);
    auto position_after = entity.GetComponent<ol::PositionComponent>();

    EXPECT_EQ(position_before.x, position_after.x);
    EXPECT_EQ(position_before.y, position_after.y);
    ASSERT_EQ(deque.GetLotsCount(), 3);
}

TEST_F(PlayfieldSystemTests, HandleEvent_CreatePlotEvent_NonCentral_ToTop)
{
    constexpr auto pos_x = 6489.f;
    constexpr auto pos_y = 4620.f;
    constexpr auto lot_type = ol::lot::Type::Begin;

    auto plot = ol::plot::getPlots(lot_type)[0];
    auto event = ol::CreatePlotEvent{ plot, lot_type, true, { pos_x, pos_y } };

    ol::systemHandleEvent(mSystem, mRegistryRef, event);

    auto entity = mSystem.GetLotDeques().at(lot_type);
    auto&& deque = entity.GetComponent<ol::LotDequeComponent>();
    auto position = entity.GetComponent<ol::PositionComponent>();

    EXPECT_EQ(position.x, pos_x);
    EXPECT_EQ(position.y, pos_y);
    ASSERT_EQ(deque.GetLotsCount(), 2);
}

TEST_F(PlayfieldSystemTests, HandleEvent_CreatePlotEvent_NonCentral_ToBottom)
{
    constexpr auto pos_x = 7011.f;
    constexpr auto pos_y = 57834.f;
    constexpr auto lot_type = ol::lot::Type::Begin;

    auto plot = ol::plot::getPlots(lot_type)[0];
    auto event = ol::CreatePlotEvent{ plot, lot_type, false, { pos_x, pos_y } };

    ol::systemHandleEvent(mSystem, mRegistryRef, event);

    auto entity = mSystem.GetLotDeques().at(lot_type);
    auto&& deque = entity.GetComponent<ol::LotDequeComponent>();
    auto position = entity.GetComponent<ol::PositionComponent>();

    EXPECT_EQ(position.x, pos_x);
    EXPECT_EQ(position.y, pos_y);
    ASSERT_EQ(deque.GetLotsCount(), 2);
}

TEST_F(PlayfieldSystemTests, HandleEvent_DrawEvent_StoresTexture)
{
    auto deque_texture_regex = std::stringstream{};
    deque_texture_regex << ol::PlayfieldSystem::kTexturePrefix << "\\d+";
    auto deque_texture_matcher = MatchesRegex(deque_texture_regex.str());

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    EXPECT_CALL(*mResourceMgr, StoreTexture(deque_texture_matcher, _))
        .WillOnce(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});
}

TEST_F(PlayfieldSystemTests, HandleEvent_DrawEvent_SetsDynamicTextureUpToDate)
{
    constexpr auto central = ol::lot::Type::Central;

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});

    auto entity = mSystem.GetLotDeques().at(central);
    auto&& texture = entity.GetComponent<ol::DynamicTextureComponent>();

    ASSERT_FALSE(texture.NeedsUpdate());
}

TEST_F(PlayfieldSystemTests, HandleEvent_DrawEvent_SetsSpritePosition)
{
    constexpr auto central = ol::lot::Type::Central;

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});

    auto entity = mSystem.GetLotDeques().at(central);
    auto&& sprite = entity.GetComponent<ol::SpriteComponent>();
    auto&& position = entity.GetComponent<ol::PositionComponent>();

    EXPECT_FLOAT_EQ(sprite.GetPosition().x, position.x);
    ASSERT_FLOAT_EQ(sprite.GetPosition().y, position.y);
}

TEST_F(PlayfieldSystemTests, HandleEvent_DrawEvent_NewPlotInvalidatesTexture)
{
    constexpr auto central = ol::lot::Type::Central;
    constexpr auto plot_type = ol::plot::kCentral;

    auto entity = mSystem.GetLotDeques().at(central);

    auto plot = ol::plot::getPlots(central)[plot_type];
    auto create_plot_event = ol::CreatePlotEvent{ plot, central, true };

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});

    ol::systemHandleEvent(mSystem, mRegistryRef, create_plot_event);
    auto&& texture = entity.GetComponent<ol::DynamicTextureComponent>();

    ASSERT_TRUE(texture.NeedsUpdate());
}

TEST_F(PlayfieldSystemTests,
       HandleEvent_DrawEvent_NewPlotInvalidatesOnlyCorrespondingDeque)
{
    constexpr auto lot_type = ol::lot::Type::Begin;
    constexpr auto central = ol::lot::Type::Central;

    auto plot = ol::plot::getPlots(lot_type)[0];
    auto create_plot_event = ol::CreatePlotEvent{ plot, lot_type, true };

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});

    ol::systemHandleEvent(mSystem, mRegistryRef, create_plot_event);

    auto entity = mSystem.GetLotDeques().at(central);
    auto&& texture = entity.GetComponent<ol::DynamicTextureComponent>();

    ASSERT_FALSE(texture.NeedsUpdate());
}

TEST_F(PlayfieldSystemTests, HandleEvent_CreateNewPlot_DrawUpdatesTextureStorage)
{
    constexpr auto central = ol::lot::Type::Central;
    constexpr auto plot_type = ol::plot::kCentral;

    auto deque_texture_regex = std::stringstream{};
    deque_texture_regex << ol::PlayfieldSystem::kTexturePrefix << "\\d+";
    auto deque_texture_matcher = MatchesRegex(deque_texture_regex.str());

    auto entity = mSystem.GetLotDeques().at(central);

    auto plot = ol::plot::getPlots(central)[plot_type];
    auto create_plot_event = ol::CreatePlotEvent{ plot, central, true };

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    EXPECT_CALL(*mResourceMgr, StoreTexture(deque_texture_matcher, _))
        .Times(2)
        .WillRepeatedly(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});

    ol::systemHandleEvent(mSystem, mRegistryRef, create_plot_event);

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});
    auto&& texture = entity.GetComponent<ol::DynamicTextureComponent>();

    ASSERT_FALSE(texture.NeedsUpdate());
}

TEST_F(PlayfieldSystemTests,
       HandleEvent_DrawEvent_NewPlotOnTopShiftsSpritePosition)
{
    constexpr auto central = ol::lot::Type::Central;
    constexpr auto plot_type = ol::plot::kCentral;

    auto entity = mSystem.GetLotDeques().at(central);
    auto sprite = entity.FindComponent<ol::SpriteComponent>();

    auto plot = ol::plot::getPlots(central)[plot_type];
    auto create_plot_event = ol::CreatePlotEvent{ plot, central, true };

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});
    auto position_before = sprite->GetPosition();

    ol::systemHandleEvent(mSystem, mRegistryRef, create_plot_event);

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});
    sprite = entity.FindComponent<ol::SpriteComponent>();

    EXPECT_FLOAT_EQ(sprite->GetPosition().x, position_before.x);
    ASSERT_LT(sprite->GetPosition().y, position_before.y);
}

TEST_F(PlayfieldSystemTests,
       HandleEvent_DrawEvent_NewPlotAtBottomDoesNotShiftSpritePosition)
{
    constexpr auto central = ol::lot::Type::Central;
    constexpr auto plot_type = ol::plot::kCentral;

    auto entity = mSystem.GetLotDeques().at(central);
    auto sprite = entity.FindComponent<ol::SpriteComponent>();

    auto plot = ol::plot::getPlots(central)[plot_type];
    auto create_plot_event = ol::CreatePlotEvent{ plot, central, false };

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillRepeatedly(ReturnRef(mTexture));

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});
    auto position_before = sprite->GetPosition();

    ol::systemHandleEvent(mSystem, mRegistryRef, create_plot_event);

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::DrawEvent{});
    sprite = entity.FindComponent<ol::SpriteComponent>();

    EXPECT_FLOAT_EQ(sprite->GetPosition().x, position_before.x);
    ASSERT_FLOAT_EQ(sprite->GetPosition().y, position_before.y);
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
