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
#include <cmath>
#include <unordered_set>
#include "Game/Systems/PlotAcquisitionSystem.hpp"
#include "Game/Systems/PlayfieldSystem.hpp"
#include "Game/LotDeque.hpp"
#include "Game/PlotAcquisitionMarker.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/InteractionAreaComponent.hpp"

namespace test
{

namespace pa = ol::plot_acquisition;
namespace ld = ol::lot_deque;
namespace lot = ol::lot;
namespace marker = ol::plot_acquisition_marker;

using ol::tile::kTileWidth;
using ol::tile::kTileHeight;

constexpr auto kCentral = lot::Type::Central;
constexpr auto kCentralDequeX = lot::getOffsetX(kCentral);
constexpr auto kCentralDequeY = 0.f;

using RectAreaComponent = ol::RectangularInteractionAreaComponent;

class PlotAcquisitionSystemTests : public ResourceManagerDefaultActionTestBase
{
protected:
    ol::Registry mRegistry;
    ol::RegistryRef mRegistryRef{ mRegistry };
    ol::PlotAcquisitionSystem mSystem{ mRegistry, mResourceMgr };

    ol::LotDequeComponent& GetCentralDeque()
    { return mCentralDeque.GetComponent<ol::LotDequeComponent>(); }

    ld::LotsInfoMap mLotsInfo{
        { kCentral - 1, ld::LotsInfo{} },
        { kCentral, ld::LotsInfo{} },
        { kCentral + 1, ld::LotsInfo{} },
    };

private:
    ol::Entity createCentralDeque()
    {
        return ld::create(mRegistryRef,
                          kCentral,
                          { kCentralDequeX, kCentralDequeY });
    }
    ol::Entity mCentralDeque = createCentralDeque();
};

TEST_F(PlotAcquisitionSystemTests, AfterConstruction_NoMarkersExist)
{
    constexpr auto expected_size = 0;

    auto&& map = mSystem.GetMarkerMap();

    ASSERT_GT(map.GetSize(), 0);
    for (auto&& [_, markers] : map) {
        ASSERT_EQ(markers.size(), expected_size);
    }
}

TEST_F(PlotAcquisitionSystemTests,
       CreateMissingMarkers_CentralLotExists_TwoCentralMarkersGetCreated)
{
    constexpr auto central_lot_count = 1;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    pa::createMissingMarkers(markers,
                             kCentral,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       CreateMissingMarkers_CentralLotExists_TwoAdjacentPlotsMarkersGetCreated)
{
    constexpr auto adjacent_type = kCentral - 1;
    constexpr auto central_lot_count = 1;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(adjacent_type);

    pa::createMissingMarkers(markers,
                             adjacent_type,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       CreateMissingMarkers_AddCentralLots_CentralMarkerCountDoesNotIncrease)
{
    constexpr auto central_lot_count = 1;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    pa::createMissingMarkers(markers,
                             kCentral,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    mLotsInfo.at(kCentral).count++;

    pa::createMissingMarkers(markers,
                             kCentral,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       CreateMissingMarkers_AddCentralLots_AdjacentPlotsMarkerCountIncreases)
{
    constexpr auto adjacent_type = kCentral - 1;
    constexpr auto central_lot_count = 1;
    constexpr auto expected_size = 3;

    mLotsInfo.at(kCentral).count = central_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(adjacent_type);

    pa::createMissingMarkers(markers,
                             adjacent_type,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    mLotsInfo.at(kCentral).count++;

    pa::createMissingMarkers(markers,
                             adjacent_type,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       CreateMissingMarkers_AddAdjacentLots_CentralMarkerCountDoesNotIncrease)
{
    constexpr auto adjacent_type = kCentral - 1;
    constexpr auto central_lot_count = 1;
    constexpr auto adjacent_lot_count = 1;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    mLotsInfo.at(adjacent_type).count = adjacent_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(adjacent_type);

    pa::createMissingMarkers(markers,
                             adjacent_type,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    mLotsInfo.at(adjacent_type).count++;

    pa::createMissingMarkers(markers,
                             adjacent_type,
                             mLotsInfo,
                             mRegistryRef,
                             mResourceMgr);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       RemoveExcessMarkers_LotsExist_TwoMarkersUntouched)
{
    constexpr auto marker_count = 2;
    constexpr auto central_lot_count = 1;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         kCentral,
                                         true,
                                         mResourceMgr));
    }

    pa::removeExcessMarkers(markers,
                            kCentral,
                            mLotsInfo,
                            mRegistryRef);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       RemoveExcessMarkers_LotsExist_AllMarkersExceptTwoAreRemoved)
{
    constexpr auto marker_count = 5;
    constexpr auto central_lot_count = 1;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         kCentral,
                                         true,
                                         mResourceMgr));
    }

    pa::removeExcessMarkers(markers,
                            kCentral,
                            mLotsInfo,
                            mRegistryRef);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
  RemoveExcessMarkers_NoAdjacentLotsExist_CentralLotCountPlusOneMarkersUntouched)
{
    constexpr auto adjacent_type = kCentral + 1;
    constexpr auto central_lot_count = 5;
    constexpr auto expected_marker_count = central_lot_count + 1;

    mLotsInfo.at(kCentral).count = central_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(adjacent_type);

    for (auto i = 0; i < expected_marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         kCentral,
                                         true,
                                         mResourceMgr));
    }

    pa::removeExcessMarkers(markers,
                            adjacent_type,
                            mLotsInfo,
                            mRegistryRef);

    ASSERT_EQ(markers.size(), expected_marker_count);
}

TEST_F(PlotAcquisitionSystemTests,
       RemoveExcessMarkers_AdjacentLotsExist_TwoCentralMarkersRemain)
{
    constexpr auto adjacent_type = kCentral + 1;
    constexpr auto adjacent_lot_count = 5;
    constexpr auto central_lot_count = 2;
    constexpr auto central_marker_count = 2;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    mLotsInfo.at(adjacent_type).count = adjacent_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    for (auto i = 0; i < central_marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         kCentral,
                                         true,
                                         mResourceMgr));
    }

    pa::removeExcessMarkers(markers,
                            kCentral,
                            mLotsInfo,
                            mRegistryRef);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       RemoveExcessMarkers_AdjacentLotsExist_MarkersForAdjacentPlotsAreRemoved)
{
    constexpr auto adjacent_type = kCentral + 1;
    constexpr auto adjacent_lot_count = 5;
    constexpr auto central_lot_count = 2;
    constexpr auto marker_count = central_lot_count + 1;
    constexpr auto expected_size = 2;

    mLotsInfo.at(kCentral).count = central_lot_count;
    mLotsInfo.at(adjacent_type).count = adjacent_lot_count;
    auto&& markers = mSystem.GetMarkerMap().Get(adjacent_type);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         adjacent_type,
                                         true,
                                         mResourceMgr));
    }

    pa::removeExcessMarkers(markers,
                            adjacent_type,
                            mLotsInfo,
                            mRegistryRef);

    ASSERT_EQ(markers.size(), expected_size);
}

TEST_F(PlotAcquisitionSystemTests,
       UpdateMarkerPositions_LotsArePresent_MarkersArePositioned)
{
    constexpr auto central_lot_count = 2;
    constexpr auto marker_count = 2;
    constexpr auto position_x = kCentralDequeX;
    constexpr auto position_y = kCentralDequeY;
    constexpr auto expected_position_upper_x = position_x;
    constexpr auto expected_position_upper_y = position_y - kTileHeight;
    constexpr auto expected_position_lower_x = position_x;
    constexpr auto expected_position_lower_y = position_y + 2 * kTileHeight;

    mLotsInfo.at(kCentral).count = central_lot_count;
    mLotsInfo.at(kCentral).position = { kCentralDequeX, kCentralDequeY };
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         kCentral,
                                         true,
                                         mResourceMgr));
    }

    pa::updateMarkerPositions(markers, kCentral, mLotsInfo);

    auto upper_position = markers[0].GetComponent<ol::PositionComponent>();
    auto lower_position = markers[1].GetComponent<ol::PositionComponent>();
    EXPECT_FLOAT_EQ(upper_position.x, expected_position_upper_x);
    EXPECT_FLOAT_EQ(upper_position.y, expected_position_upper_y);
    EXPECT_FLOAT_EQ(lower_position.x, expected_position_lower_x);
    ASSERT_FLOAT_EQ(lower_position.y, expected_position_lower_y);
}

TEST_F(PlotAcquisitionSystemTests,
       UpdateMarkerPositions_LotsAreNotPresent_MarkersArePositioned)
{
    constexpr auto adjacent_type = kCentral + 1;
    constexpr auto central_lot_count = 2;
    constexpr auto marker_count = 3;
    constexpr auto expected_x = lot::getOffsetX(adjacent_type);
    constexpr auto expected_upper_y = static_cast<float>(kTileHeight) * -1.f;
    constexpr auto expected_middle_y = 0.f;
    constexpr auto expected_lower_y = static_cast<float>(kTileHeight);

    mLotsInfo.at(kCentral).count = central_lot_count;
    mLotsInfo.at(kCentral).position = { kCentralDequeX, kCentralDequeY };
    auto&& markers = mSystem.GetMarkerMap().Get(adjacent_type);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         adjacent_type,
                                         true,
                                         mResourceMgr));
    }

    pa::updateMarkerPositions(markers, adjacent_type, mLotsInfo);

    auto upper_position = markers[0].GetComponent<ol::PositionComponent>();
    auto middle_position = markers[1].GetComponent<ol::PositionComponent>();
    auto lower_position = markers[2].GetComponent<ol::PositionComponent>();
    EXPECT_EQ(upper_position.x, expected_x);
    EXPECT_EQ(middle_position.x, expected_x);
    EXPECT_EQ(lower_position.x, expected_x);
    EXPECT_EQ(upper_position.y, expected_upper_y);
    EXPECT_EQ(middle_position.y, expected_middle_y);
    ASSERT_EQ(lower_position.y, expected_lower_y);
}

TEST_F(PlotAcquisitionSystemTests, UpdateMarkerInteractionAreas_TwoMarkers_Upper)
{
    constexpr auto marker_count = 2;
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;

    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         kCentral,
                                         true,
                                         mResourceMgr));
    }

    auto marker = markers.front();
    const auto& marker_area = marker.GetComponent<RectAreaComponent>();

    pa::updateMarkerInteractionAreas(markers);

    const auto marker_size = marker::getSize(kCentral);
    const auto overlap = marker::kMarkerOverlapFactor * marker_size.y;
    const auto in_bounds_x = position_x + marker_size.x / 2;
    const auto in_bounds_y1 = position_y + marker_size.y / 2;
    const auto in_bounds_y2 = position_y + marker_size.y - overlap / 2;
    EXPECT_TRUE(marker_area.IsPointInArea({ in_bounds_x, in_bounds_y1 }));
    ASSERT_TRUE(marker_area.IsPointInArea({ in_bounds_x, in_bounds_y2 }));
}

TEST_F(PlotAcquisitionSystemTests, UpdateMarkerInteractionAreas_TwoMarkers_Lower)
{
    constexpr auto marker_count = 2;
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;

    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         kCentral,
                                         true,
                                         mResourceMgr));
    }

    auto marker = markers.back();
    const auto& marker_area = marker.GetComponent<RectAreaComponent>();

    pa::updateMarkerInteractionAreas(markers);

    const auto marker_size = marker::getSize(kCentral);
    const auto overlap = marker::kMarkerOverlapFactor * marker_size.y;
    const auto in_bounds_x = position_x + marker_size.x / 2;
    const auto in_bounds_y1 = position_y + marker_size.y / 2;
    const auto in_bounds_y2 = position_y + marker_size.y - overlap / 2;
    EXPECT_TRUE(marker_area.IsPointInArea({ in_bounds_x, in_bounds_y1 }));
    ASSERT_TRUE(marker_area.IsPointInArea({ in_bounds_x, in_bounds_y2 }));
}

TEST_F(PlotAcquisitionSystemTests,
       UpdateMarkerInteractionAreas_OverTwoMarkers_Upper)
{
    constexpr auto lot_type = kCentral + 1;
    constexpr auto marker_count = 3;
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;

    auto&& markers = mSystem.GetMarkerMap().Get(lot_type);
    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         lot_type,
                                         true,
                                         mResourceMgr));
    }

    auto marker = markers.front();
    const auto& marker_area = marker.GetComponent<RectAreaComponent>();

    auto marker_size = marker::getSize(lot_type);
    const auto overlap = marker::kMarkerOverlapFactor * marker_size.y;
    const auto in_bounds_x = position_x + marker_size.x / 2;
    const auto in_bounds_y = position_y + marker_size.y / 2;
    const auto out_of_bounds_y = position_y + marker_size.y - overlap / 2;

    pa::updateMarkerInteractionAreas(markers);

    EXPECT_FALSE(marker_area.IsPointInArea({ in_bounds_x, out_of_bounds_y }));
    ASSERT_TRUE(marker_area.IsPointInArea({ in_bounds_x, in_bounds_y }));
}

TEST_F(PlotAcquisitionSystemTests,
       UpdateMarkerInteractionAreas_OverTwoMarkers_Middle)
{
    constexpr auto lot_type = kCentral + 1;
    constexpr auto marker_count = 3;
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;

    auto&& markers = mSystem.GetMarkerMap().Get(lot_type);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         lot_type,
                                         true,
                                         mResourceMgr));
    }

    auto marker = markers[1];
    const auto& marker_area = marker.GetComponent<RectAreaComponent>();
    auto&& upper_position = markers[0].GetComponent<ol::PositionComponent>();
    auto&& lower_position = markers[2].GetComponent<ol::PositionComponent>();
    upper_position.y = kTileHeight * -1.f;
    lower_position.y = static_cast<float>(kTileHeight);

    pa::updateMarkerInteractionAreas(markers);

    auto marker_size = marker::getSize(lot_type);
    const auto in_bounds_x = position_x + marker_size.x / 2;
    const auto in_bounds_y = position_y + marker_size.y / 2;
    const auto out_of_bounds_y1 = position_y + 5.f;
    const auto out_of_bounds_y2 = position_y + marker_size.y - 5.f;
    EXPECT_FALSE(marker_area.IsPointInArea({ in_bounds_x, out_of_bounds_y1 }));
    EXPECT_FALSE(marker_area.IsPointInArea({ in_bounds_x, out_of_bounds_y2 }));
    ASSERT_TRUE(marker_area.IsPointInArea({ in_bounds_x, in_bounds_y }));
}

TEST_F(PlotAcquisitionSystemTests,
       UpdateMarkerInteractionAreas_OverTwoMarkers_Lower)
{
    constexpr auto lot_type = kCentral + 1;
    constexpr auto marker_count = 3;
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;

    auto&& markers = mSystem.GetMarkerMap().Get(lot_type);

    for (auto i = 0; i < marker_count; ++i) {
        markers.push_back(marker::create(mRegistryRef,
                                         lot_type,
                                         true,
                                         mResourceMgr));
    }

    auto marker = markers[2];
    const auto& marker_area = marker.GetComponent<RectAreaComponent>();


    pa::updateMarkerInteractionAreas(markers);

    auto marker_size = marker::getSize(lot_type);
    const auto overlap = marker::kMarkerOverlapFactor * marker_size.y;
    const auto in_bounds_x = position_x + marker_size.x / 2;
    const auto in_bounds_y = position_y + marker_size.y / 2;
    const auto out_of_bounds_y = position_y + overlap / 2;
    EXPECT_FALSE(marker_area.IsPointInArea({ in_bounds_x, out_of_bounds_y }));
    ASSERT_TRUE(marker_area.IsPointInArea({ in_bounds_x, in_bounds_y }));
}

TEST_F(PlotAcquisitionSystemTests,
       SystemHandleEvent_UpdateMarkersEvent_CentralMarkersAreCreated)
{
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);
    GetCentralDeque().AddLotToTop({ 0 });

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::UpdateMarkersEvent{});

    ASSERT_EQ(markers.size(), 2);
}

TEST_F(PlotAcquisitionSystemTests,
       SystemHandleEvent_UpdateMarkersEvent_MarkersForAdjacentPlotsAreCreated)
{
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral + 1);
    GetCentralDeque().AddLotToTop({ 0 });
    GetCentralDeque().AddLotToTop({ 0 });

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::UpdateMarkersEvent{});

    ASSERT_EQ(markers.size(), 3);
}

TEST_F(PlotAcquisitionSystemTests,
       SystemHandleEvent_UpdateMarkersEvent_TwoCentralMarkersRemain)
{
    constexpr auto marker_count = 6;

    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);
    GetCentralDeque().AddLotToTop({ 0 });

    for (auto i = 0; i < marker_count; ++i) {
        markers.emplace_back(marker::create(mRegistryRef,
                                            kCentral,
                                            true,
                                            mResourceMgr));
    }

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::UpdateMarkersEvent{});

    ASSERT_EQ(markers.size(), 2);
}

TEST_F(PlotAcquisitionSystemTests,
       SystemHandleEvent_UpdateMarkersEvent_CentralMarkerArePositioned)
{
    constexpr auto expected_x = ol::lot::getTileCount(kCentral - 1) * kTileWidth;
    constexpr auto expected_upper_y = kTileHeight * -1.f;
    constexpr auto expected_lower_y = kTileHeight;

    GetCentralDeque().AddLotToBottom({ 0 });

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::UpdateMarkersEvent{});

    auto&& markers = mSystem.GetMarkerMap().Get(kCentral);
    auto upper_position = markers[0].GetComponent<ol::PositionComponent>();
    auto lower_position = markers[1].GetComponent<ol::PositionComponent>();
    EXPECT_EQ(upper_position.x, expected_x);
    EXPECT_EQ(lower_position.x, expected_x);
    EXPECT_EQ(upper_position.y, expected_upper_y);
    ASSERT_EQ(lower_position.y, expected_lower_y);
}

TEST_F(PlotAcquisitionSystemTests,
       SystemHandleEvent_UpdateMarkersEvent_MarkersForAdjacentPlotsArePositioned)
{
    constexpr auto lot_type = kCentral - 1;
    constexpr auto expected_x = 0.f;
    constexpr auto expected_upper_y = static_cast<float>(kTileHeight) * -1.f;
    constexpr auto expected_middle_y = 0.f;
    constexpr auto expected_lower_y = static_cast<float>(kTileHeight);

    GetCentralDeque().AddLotToBottom({ 0 });
    GetCentralDeque().AddLotToBottom({ 0 });

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::UpdateMarkersEvent{});

    auto&& markers = mSystem.GetMarkerMap().Get(lot_type);
    auto upper_position = markers[0].GetComponent<ol::PositionComponent>();
    auto middle_position = markers[1].GetComponent<ol::PositionComponent>();
    auto lower_position = markers[2].GetComponent<ol::PositionComponent>();
    EXPECT_EQ(upper_position.x, expected_x);
    EXPECT_EQ(middle_position.x, expected_x);
    EXPECT_EQ(lower_position.x, expected_x);
    EXPECT_EQ(upper_position.y, expected_upper_y);
    EXPECT_EQ(middle_position.y, expected_middle_y);
    ASSERT_EQ(lower_position.y, expected_lower_y);
}

TEST_F(PlotAcquisitionSystemTests,
       SystemHandleEvent_UpdateMarkersEvent_InteractionAreasAreUpdated)
{
    constexpr auto dt = 5.f;
    constexpr auto point_count = static_cast<int>(kTileHeight * 2 / dt);

    auto points = std::vector<ol::Vector2f>{};
    points.reserve(point_count);
    for (int i = 0; i < point_count; ++i) {
        points.emplace_back(kCentralDequeX - kTileWidth, dt * i - kTileHeight);
    }

    GetCentralDeque().AddLotToBottom({ 0 });
    auto&& markers = mSystem.GetMarkerMap().Get(kCentral - 1);

    ol::systemHandleEvent(mSystem, mRegistryRef, ol::UpdateMarkersEvent{});

    for (auto point : points) {
        auto result = std::find_if(markers.cbegin(), markers.cend(), [&point]
        (auto marker)
        {
            auto&& area = marker.template GetComponent<RectAreaComponent>();
            auto pos = marker.template GetComponent<ol::PositionComponent>();
            point.x -= pos.x;
            point.y -= pos.y;
            return area.IsPointInArea(point);
        });

        ASSERT_NE(result, markers.end());
    }
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
