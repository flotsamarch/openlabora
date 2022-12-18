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
#include "Game/PlotAcquisitionMarker.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "ECS/MassAssignComponents.hpp"
#include "Game/Components/PlotAcquireInfoComponent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/SelectableComponent.hpp"
#include "Game/Components/SignalComponent.hpp"
#include "Game/Components/InteractionAreaComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"

namespace test
{

using testing::Return;
using testing::ReturnRef;
using testing::AtLeast;
using testing::MatchesRegex;
using RectAreaComponent = ol::RectangularInteractionAreaComponent;

namespace marker = ol::plot_acquisition_marker;


class PlotAcquisitionMarkerTests : public ResourceManagerDefaultActionTestBase
{
protected:
    ol::Registry mRegistry;
    ol::RegistryRef mRegistryRef{ mRegistry };

    // Should be EndsWith but currently it does not work with std::string_view
    // Same as EndsWith("_marker")
    inline static const auto kMatchMarkerTexture = MatchesRegex("^\\w+_marker$");

};

constexpr auto kLotType = ol::lot::Type::Begin;

TEST_F(PlotAcquisitionMarkerTests, Create_AddsEntityToRegistry)
{
    marker::create(mRegistryRef, kLotType, true, mResourceMgr);

    ASSERT_EQ(mRegistry.EntityCount(), 1);
}

TEST_F(PlotAcquisitionMarkerTests, Create_EntityHasPlotAcquireInfoComponent)
{
    auto marker = marker::create(mRegistryRef, kLotType, true, mResourceMgr);

    ASSERT_NE(marker.FindComponent<ol::PlotAcquireInfoComponent>(), nullptr);
}

TEST_F(PlotAcquisitionMarkerTests, Create_EntityHasPositionComponent)
{
    auto marker = marker::create(mRegistryRef, kLotType, true, mResourceMgr);

    ASSERT_NE(marker.FindComponent<ol::PositionComponent>(), nullptr);
}

TEST_F(PlotAcquisitionMarkerTests, Create_EntityHasSelectableComponent)
{
    auto marker = marker::create(mRegistryRef, kLotType, true, mResourceMgr);

    ASSERT_NE(marker.FindComponent<ol::SelectableComponent>(), nullptr);
}

TEST_F(PlotAcquisitionMarkerTests, Create_EntityHasSignalComponent)
{
    auto marker = marker::create(mRegistryRef, kLotType, true, mResourceMgr);

    ASSERT_NE(marker.FindComponent<ol::SignalComponent>(), nullptr);
}

TEST_F(PlotAcquisitionMarkerTests, Create_EntityHasInteractionAreaComponent)
{
    auto marker = marker::create(mRegistryRef, kLotType, true, mResourceMgr);

    ASSERT_NE(marker.FindComponent<RectAreaComponent>(), nullptr);
}

TEST_F(PlotAcquisitionMarkerTests, Create_EntityHasSpriteComponent)
{
    auto marker = marker::create(mRegistryRef, kLotType, true, mResourceMgr);

    ASSERT_NE(marker.FindComponent<ol::SpriteComponent>(), nullptr);
}

TEST_F(PlotAcquisitionMarkerTests, Create_CallsGetTextureOnce)
{
    EXPECT_CALL(*mResourceMgr, GetTexture)
        .WillOnce(Return(mTexture));

    marker::create(mRegistryRef, ol::lot::Type::Begin, true, mResourceMgr);
}

TEST_F(PlotAcquisitionMarkerTests, Create_CallsStoreTextureOnce)
{
    EXPECT_CALL(*mResourceMgr, GetTexture)
        .Times(AtLeast(1))
        .WillRepeatedly(Return(mTexture));

    EXPECT_CALL(*mResourceMgr, GetTexture(kMatchMarkerTexture))
        .WillOnce(Return(std::nullopt));

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .WillOnce(ReturnRef(mTexture));

    marker::create(mRegistryRef, ol::lot::Type::Begin, true, mResourceMgr);
}

constexpr auto kBeginLotIndex = static_cast<int>(ol::lot::Type::Begin);
constexpr auto kEndLotIndex = static_cast<int>(ol::lot::Type::End);
constexpr auto kLotsCount = kEndLotIndex - kBeginLotIndex;

TEST_F(PlotAcquisitionMarkerTests,
       InitializeSpriteComponent_CallsGetTextureOnceForEachLotType)
{
    EXPECT_CALL(*mResourceMgr, GetTexture)
        .Times(kLotsCount)
        .WillRepeatedly(Return(mTexture));

    for (auto type = ol::lot::Type::Begin; type != ol::lot::Type::End; ++type) {
        auto marker = mRegistry.CreateEntity();

        ol::MassAssignComponents{ marker }
            .Assign<ol::SpriteComponent>()
            .Assign<ol::PlotAcquireInfoComponent>(type, true);

        marker::initilizeSpriteComponent(marker, mResourceMgr);
    }
}

TEST_F(PlotAcquisitionMarkerTests,
       InitializeSpriteComponent_CallsStoreTextureOnceForEachLotType)
{
    EXPECT_CALL(*mResourceMgr, GetTexture)
        .Times(AtLeast(1))
        .WillRepeatedly(Return(mTexture));

    EXPECT_CALL(*mResourceMgr, GetTexture(kMatchMarkerTexture))
        .Times(kLotsCount)
        .WillRepeatedly(Return(std::nullopt));

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .Times(kLotsCount)
        .WillRepeatedly(ReturnRef(mTexture));

    for (auto type = ol::lot::Type::Begin; type != ol::lot::Type::End; ++type) {
        auto marker = mRegistry.CreateEntity();

        ol::MassAssignComponents{ marker }
            .Assign<ol::SpriteComponent>()
            .Assign<ol::PlotAcquireInfoComponent>(type, true);

        marker::initilizeSpriteComponent(marker, mResourceMgr);
    }
}

TEST_F(PlotAcquisitionMarkerTests,
       InitializeSpriteComponent_DoesNotCallStoreTextureIfTextureExists)
{
    EXPECT_CALL(*mResourceMgr, GetTexture)
        .WillOnce(Return(mTexture));

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .Times(0);

    auto marker = mRegistry.CreateEntity();

    ol::MassAssignComponents{ marker }
        .Assign<ol::SpriteComponent>()
        .Assign<ol::PlotAcquireInfoComponent>(ol::lot::Type::Begin, true);

    marker::initilizeSpriteComponent(marker, mResourceMgr);
}

TEST_F(PlotAcquisitionMarkerTests, getLotType)
{
    for (auto type = ol::lot::Type::Begin; type != ol::lot::Type::End; ++type) {
        auto marker = marker::create(mRegistryRef,
                                     type,
                                     true,
                                     mResourceMgr);

        auto ret_type = marker::getLotType(marker);

        ASSERT_EQ(type, ret_type);
    }
}

TEST_F(PlotAcquisitionMarkerTests, SetPosition_UpdatesPositionComponent)
{
    constexpr auto position_x = 15.f;
    constexpr auto position_y = 1555.f;

    auto marker = marker::create(mRegistryRef,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    auto new_position = marker.GetComponent<ol::PositionComponent>();

    EXPECT_FLOAT_EQ(position_x, new_position.x);
    ASSERT_FLOAT_EQ(position_y, new_position.y);
}

TEST_F(PlotAcquisitionMarkerTests, SetPosition_NotEqualOldPosition)
{
    constexpr auto position_x = 15.f;
    constexpr auto position_y = 1555.f;

    auto marker = marker::create(mRegistryRef,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    auto old_position = marker.GetComponent<ol::PositionComponent>();
    marker::setPosition(marker, { position_x, position_y });
    auto new_position = marker.GetComponent<ol::PositionComponent>();

    EXPECT_NE(old_position.x, new_position.x);
    ASSERT_NE(old_position.y, new_position.y);
}

TEST_F(PlotAcquisitionMarkerTests,
       SetInteractiveRect_UpdatesInteractiveRectOffset)
{
    constexpr auto offset_x = 15.f;
    constexpr auto offset_y = 1555.f;
    constexpr auto width = 325.f;
    constexpr auto height = 7771.f;

    auto marker = marker::create(mRegistryRef,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setInteractiveRect(marker,
                               { offset_x, offset_y },
                               { width, height });

    auto new_area = marker.GetComponent<RectAreaComponent>();

    EXPECT_FLOAT_EQ(new_area.GetOffset().x, offset_x);
    ASSERT_FLOAT_EQ(new_area.GetOffset().y, offset_y);
}

TEST_F(PlotAcquisitionMarkerTests,
       SetInteractiveRect_UpdatesInteractiveRect_IsPointInArea)
{
    constexpr auto offset_x = 15.f;
    constexpr auto offset_y = 1555.f;
    constexpr auto width = 325.f;
    constexpr auto height = 7771.f;

    auto marker = marker::create(mRegistryRef,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setInteractiveRect(marker,
                               { offset_x, offset_y },
                               { width, height });

    auto new_area = marker.GetComponent<RectAreaComponent>();

    const auto sum_x = offset_x + width;
    const auto sum_y = offset_y + height;

    EXPECT_FALSE(new_area.IsPointInArea({ offset_x - 1.f, offset_x - 1.f }));
    EXPECT_FALSE(new_area.IsPointInArea({ sum_x + 1.f, sum_y + 1.f }));
    EXPECT_TRUE(new_area.IsPointInArea({ offset_x + 1.f, offset_y + 1.f }));
    ASSERT_TRUE(new_area.IsPointInArea({ sum_x - 1.f, sum_y - 1.f }));
}

TEST(PlotAcquisitionMarkerFreeFunctionsTests,
     GetSize_WidthAlwaysGreaterThanDoubleTileWidth)
{
    for (auto type = ol::lot::Type::Begin; type != ol::lot::Type::End; ++type) {
        auto size = marker::getSize(type);

        ASSERT_GE(size.x, ol::tile::kTileWidth * 2);
    }
}

TEST(PlotAcquisitionMarkerFreeFunctionsTests,
     GetSize_HeightAlwaysGreaterThanTileHeight)
{
    for (auto type = ol::lot::Type::Begin; type != ol::lot::Type::End; ++type) {
        auto size = marker::getSize(type);

        ASSERT_GE(size.y, ol::tile::kTileHeight);
    }
}

TEST(PlotAcquisitionMarkerFreeFunctionsTests,
     GetTextures_ReturnsNonEmptyContainer)
{
    for (auto type = ol::lot::Type::Begin; type != ol::lot::Type::End; ++type) {
        auto ids = marker::getTextures(type);

        ASSERT_FALSE(ids.empty());
    }
}

TEST(PlotAcquisitionMarkerFreeFunctionsTests, GetTextures_IdsNotEmptyStrings)
{
    for (auto type = ol::lot::Type::Begin; type != ol::lot::Type::End; ++type) {
        auto ids = marker::getTextures(type);

        for (auto&& id : ids) {
            ASSERT_FALSE(id.empty());
        }
    }
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
