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
#include "Game/Components/MarkerControllerComponent.hpp"
#include "Game/Playfield.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"

using OpenLabora::MarkerControllerComponent;

namespace Test
{

using OpenLabora::Playfield;
using OpenLabora::ecs::getComponent;
using PlotType = OpenLabora::plot::Type;
using TestBase = ResourceManagerDefaultActionTestBase;

class MarkerControllerComponentTests : public TestBase
{
protected:
    Playfield::Ptr mPlayfield{ OpenLabora::playfield::create(mResourceMgr, {}) };
    MarkerControllerComponent mComponent{};
};

TEST_F(MarkerControllerComponentTests, IsEmptyByDefault)
{
    for (auto&& [_, markers] : mComponent.GetMarkers()) {
        EXPECT_TRUE(markers.empty());
    }
}

TEST_F(MarkerControllerComponentTests, CreateMissingMarkers_NotEmptyAfterCall)
{
    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);

    for (auto&& [_, markers] : mComponent.GetMarkers()) {
        EXPECT_FALSE(markers.empty());
    }
}

TEST_F(MarkerControllerComponentTests,
       CreateMissingMarkers_CreatesFillingMarkersWhenAddingCentralPlots)
{
    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);
    const auto& plot = create(PlotType::Central, {}, mResourceMgr);

    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);

    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);

    for (auto&& [type, markers] : mComponent.GetMarkers()) {
        if (type != PlotType::Central) {
            EXPECT_GT(markers.size(), 2);
        }
    }
}

TEST_F(MarkerControllerComponentTests,
       CreateMissingMarkers_CreateFillingMarkersTwoStep)
{
    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);
    const auto& plot = create(PlotType::Central, {}, mResourceMgr);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);

    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);

    auto markers_count = OpenLabora::EnumMap<PlotType, size_t>{};
    for (auto&& [type, markers] : mComponent.GetMarkers()) {
        markers_count[type] = markers.size();
    }

    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);
    pf_cmpnt.AddPlotToTop(plot);

    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);

    for (auto&& [type, markers] : mComponent.GetMarkers()) {
        if (type != PlotType::Central) {
            EXPECT_GT(markers.size(), markers_count[type]);
        }
    }
}

TEST_F(MarkerControllerComponentTests, RemoveExcess_DoesNothingByDefault)
{
    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);
    mComponent.RemoveExcessMarkers(mPlayfield);

    for (auto&& [_, markers] : mComponent.GetMarkers()) {
        EXPECT_FALSE(markers.empty());
    }
}

TEST_F(MarkerControllerComponentTests, RemoveExcess_RemovesFillingMarkers)
{
    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);

    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);

    const auto& plot = create(PlotType::Begin, {}, mResourceMgr);
    pf_cmpnt.AddPlotToTop(plot);

    mComponent.RemoveExcessMarkers(mPlayfield);

    auto pred = [] (auto&& item)
    { return item.first == PlotType::Begin && item.second.size() == 2; };

    auto markers = mComponent.GetMarkers();
    ASSERT_NE(std::find_if(markers.begin(), markers.end(), pred), markers.end());

}

TEST_F(MarkerControllerComponentTests,
       RemoveExcess_RemovesAllMarkersWhenLimitIsReached)
{
    using OpenLabora::plot::create;
    auto&& pf_cmpnt = getComponent<OpenLabora::PlayfieldComponent>(*mPlayfield);
    auto markers_count = OpenLabora::EnumMap<PlotType, size_t>{};

    {
        auto&& markers = mComponent.GetMarkers();
        for (auto&& [type, markers] : markers) {
            const auto& plot = create(type, {}, mResourceMgr);

            while (!pf_cmpnt.IsPlotsLimitReached(type)) {
                pf_cmpnt.AddPlotToTop(plot);
                mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);
            }
            markers_count[type] = markers.size();
        };

        mComponent.RemoveExcessMarkers(mPlayfield);
    }
    auto pred = [] (auto&& item) { return item.second >= 2; };
    EXPECT_TRUE(std::all_of(markers_count.cbegin(), markers_count.cend(), pred));

    auto&& markers = mComponent.GetMarkers();
    auto is_empty = [] (auto&& item) { return item.second.size() == 0; };
    ASSERT_TRUE(std::all_of(markers.begin(), markers.end(), is_empty));
}

TEST_F(MarkerControllerComponentTests, GetSelectedMarker_NullptrByDefault)
{
    ASSERT_EQ(mComponent.GetSelecterMarker(), nullptr);
}

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

TEST_F(MarkerControllerComponentTests,
       ForwardEventToMarkers_MarkerIsSelectedOnClick)
{
    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);
    mComponent.TranslateMarkers(mPlayfield);

    SimulateClickOnUpperMarker(PlotType::Coastal, mComponent, mPlayfield);

    ASSERT_NE(mComponent.GetSelecterMarker(), nullptr);
}

TEST_F(MarkerControllerComponentTests, DeselectMarker)
{
    mComponent.CreateMissingMarkers(mPlayfield, [] {}, mResourceMgr);
    mComponent.TranslateMarkers(mPlayfield);

    SimulateClickOnUpperMarker(PlotType::Coastal, mComponent, mPlayfield);
    mComponent.DeselectMarker();

    ASSERT_EQ(mComponent.GetSelecterMarker(), nullptr);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
