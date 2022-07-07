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
#include "Game/MarkerController.hpp"
#include "Game/Playfield.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "Misc/UID.hpp"

namespace Test
{

using OpenLabora::Playfield;
using OpenLabora::ecs::getComponent;
using OpenLabora::MarkerController;
using PlotType = OpenLabora::plot::Type;
using TestBase = ResourceManagerDefaultActionTestBase;

class MarkerControllerTests : public TestBase
{
protected:
    Playfield::Ptr mPlayfield{ OpenLabora::playfield::create(mResourceMgr, {}) };
    MarkerController::Ptr mController{ std::make_shared<MarkerController>() };
};

TEST_F(MarkerControllerTests, IsEmptyByDefault)
{
    for (auto&& [_, markers] : mController->GetMarkers()) {
        EXPECT_TRUE(markers.empty());
    }
}

TEST_F(MarkerControllerTests, CreateMissingMarkers_NotEmptyAfterCall)
{
    auto registrar = [] (OpenLabora::ExpansionMarker::Ptr)
    { return OpenLabora::uid::getUid(); };

    mController->CreateMissingMarkers(mPlayfield,
                                      registrar,
                                      [] {},
                                      mResourceMgr);

    for (auto&& [_, markers] : mController->GetMarkers()) {
        EXPECT_FALSE(markers.empty());
    }
}

TEST_F(MarkerControllerTests, CreateMissingMarkers_DefaultAmount)
{
    auto counter{ 0u };
    constexpr auto expected_amount_of_created_markers{ 8u };
    auto registrar = [&counter] (OpenLabora::ExpansionMarker::Ptr)
    {
        counter++;
        return OpenLabora::uid::getUid();
    };

    mController->CreateMissingMarkers(mPlayfield,
                                      registrar,
                                      [] {},
                                      mResourceMgr);

    ASSERT_EQ(counter, expected_amount_of_created_markers);
}

TEST_F(MarkerControllerTests,
       CreateMissingMarkers_CreatesFillingMarkersWhenAddingCentralPlots)
{
    auto counter{ 0u };
    constexpr auto expected_amount_of_created_markers{ 14u };
    auto registrar = [&counter] (OpenLabora::ExpansionMarker::Ptr)
    {
        counter++;
        return OpenLabora::uid::getUid();
    };

    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);
    const auto& plot = create(PlotType::Central, {}, mResourceMgr);

    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);

    mController->CreateMissingMarkers(mPlayfield,
                                      registrar,
                                      [] {},
                                      mResourceMgr);

    for (auto&& [type, markers] : mController->GetMarkers()) {
        if (type != PlotType::Central) {
            EXPECT_GT(markers.size(), 2);
        }
    }
    ASSERT_EQ(counter, expected_amount_of_created_markers);
}

TEST_F(MarkerControllerTests,
       CreateMissingMarkers_CreateFillingMarkersTwoStep)
{
    auto counter{ 0u };
    constexpr auto expected_amount_of_created_markers{ 14u };
    auto registrar = [&counter] (OpenLabora::ExpansionMarker::Ptr)
    {
        counter++;
        return OpenLabora::uid::getUid();
    };

    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);
    const auto& plot = create(PlotType::Central, {}, mResourceMgr);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);

    mController->CreateMissingMarkers(mPlayfield,
                                      registrar,
                                      [] {},
                                      mResourceMgr);

    auto markers_count = OpenLabora::EnumMap<PlotType, size_t>{};
    for (auto&& [type, markers] : mController->GetMarkers()) {
        markers_count[type] = markers.size();
    }

    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);

    mController->CreateMissingMarkers(mPlayfield,
                                      registrar,
                                      [] {},
                                      mResourceMgr);

    for (auto&& [type, markers] : mController->GetMarkers()) {
        if (type != PlotType::Central) {
            EXPECT_GT(markers.size(), markers_count[type]);
        }
    }
    ASSERT_EQ(counter, expected_amount_of_created_markers);
}

TEST_F(MarkerControllerTests, RemoveExcess_DoesNothingByDefault)
{
    bool called{ false };

    auto registrar = [] (OpenLabora::ExpansionMarker::Ptr)
    {
        return OpenLabora::uid::getUid();
    };

    auto deleter = [&called] (std::span<OpenLabora::uid::Uid>)
    { called = true; };

    mController->CreateMissingMarkers(mPlayfield,
                                      registrar,
                                      [] {},
                                      mResourceMgr);

    mController->RemoveExcessMarkers(mPlayfield, deleter);

    for (auto&& [_, markers] : mController->GetMarkers()) {
        EXPECT_FALSE(markers.empty());
    }
    ASSERT_FALSE(called);
}

TEST_F(MarkerControllerTests, RemoveExcess_RemovesFillingMarkers)
{
    bool called{ false };

    auto registrar = [] (OpenLabora::ExpansionMarker::Ptr)
    {
        return OpenLabora::uid::getUid();
    };

    auto deleter = [&called] (std::span<OpenLabora::uid::Uid>)
    { called = true; };

    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);

    mController->CreateMissingMarkers(mPlayfield,
                                      registrar,
                                      [] {},
                                      mResourceMgr);

    const auto& plot = create(PlotType::Begin, {}, mResourceMgr);
    pf_cmpnt.AddPlotToTop(plot);

    mController->RemoveExcessMarkers(mPlayfield, deleter);

    auto pred = [] (auto&& item)
    { return item.first == PlotType::Begin && item.second.size() == 2; };

    auto markers = mController->GetMarkers();
    EXPECT_TRUE(called);
    ASSERT_NE(std::find_if(markers.begin(), markers.end(), pred), markers.end());
}

TEST_F(MarkerControllerTests,
       RemoveExcess_RemovesAllMarkersWhenLimitIsReached)
{
    bool called{ false };

    auto registrar = [] (OpenLabora::ExpansionMarker::Ptr)
    {
        return OpenLabora::uid::getUid();
    };

    auto deleter = [&called] (std::span<OpenLabora::uid::Uid>)
    { called = true; };

    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);
    auto markers_count = OpenLabora::EnumMap<PlotType, size_t>{};

    for (auto&& [type, markers] : mController->GetMarkers()) {
        const auto& plot = create(type, {}, mResourceMgr);

        while (!pf_cmpnt.IsPlotsLimitReached(type)) {
            pf_cmpnt.AddPlotToTop(plot);
            mController->CreateMissingMarkers(mPlayfield,
                                              registrar,
                                              [] {},
                                              mResourceMgr);
        }
        markers_count[type] = markers.size();
    };

    mController->RemoveExcessMarkers(mPlayfield,
                                     deleter);

    auto pred = [] (auto&& item) { return item.second >= 2; };
    EXPECT_TRUE(std::all_of(markers_count.cbegin(), markers_count.cend(), pred));

    auto&& markers = mController->GetMarkers();
    auto is_empty = [] (auto&& item) { return item.second.size() == 0; };
    EXPECT_TRUE(called);
    ASSERT_TRUE(std::all_of(markers.begin(), markers.end(), is_empty));
}

TEST_F(MarkerControllerTests, GetSelectedMarker_NullptrByDefault)
{
    ASSERT_EQ(mController->GetSelecterMarker(), nullptr);
}

#if 0 // TODO: Make event handling actually testable
void SimulateClickOnUpperMarker(PlotType type,
                                const MarkerControllerComponent& component,
                                Playfield::PtrConst playfield)
{
    using OpenLabora::marker::GetBoundaryMarkerPositions;
    const auto& [upper_pos, _] = GetBoundaryMarkerPositions(type, playfield);
    auto fake_mouse_pos = upper_pos + sf::Vector2f{ 1.f, 1.f };

    sf::Event event;
    event.type = sf::Event::MouseMoved;
    component.ForwardEventToMarkers(fake_mouse_pos, event);

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    component.ForwardEventToMarkers(fake_mouse_pos, event);

    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    component.ForwardEventToMarkers(fake_mouse_pos, event);
}

TEST_F(MarkerControllerTests,
       ForwardEventToMarkers_MarkerIsSelectedOnClick)
{
    mController->CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);
    mController->TranslateMarkers(mPlayfield);

    SimulateClickOnUpperMarker(PlotType::Coastal, mController, mPlayfield);

    ASSERT_NE(mController->GetSelecterMarker(), nullptr);
}

TEST_F(MarkerControllerTests, DeselectMarker)
{
    mController->CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);
    mController->TranslateMarkers(mPlayfield);

    SimulateClickOnUpperMarker(PlotType::Coastal, mController, mPlayfield);
    mController->DeselectMarker();

    ASSERT_EQ(mController->GetSelecterMarker(), nullptr);
}
#endif

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
