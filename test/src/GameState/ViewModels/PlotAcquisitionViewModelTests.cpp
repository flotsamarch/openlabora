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
#include "GameState/ViewModels/PlotAcquisitionViewModel.hpp"
#include "GameState/ModelMock.hpp"
#include "Game/PlotAcquisitionMarker.hpp"
#include "ECS/System.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"

namespace test
{

namespace ol = open_labora;
namespace marker = ol::plot_acquisition_marker;

using testing::NiceMock;
using testing::ReturnRef;

using TestModel = NiceMock<ModelMock>;
using TestPlotAcquisitionViewModel = ol::PlotAcquisitionViewModel<TestModel>;

class PlotAcquisitionViewModelTests : public ResourceManagerDefaultActionTestBase
{
protected:
    ol::Registry mRegistry;
    TestModel mModel{};
    TestPlotAcquisitionViewModel mViewModel{ ol::PtrView{ &mModel } };
};

TEST_F(PlotAcquisitionViewModelTests,
       HighlightMarker_OutOfInteractiveArea_HasBeenEnteredFalse)
{
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;
    constexpr auto width = 1.f;
    constexpr auto height = 1.f;
    constexpr auto mouse_x = position_x + 1.5f * width;
    constexpr auto mouse_y = position_y + 1.5f * height;

    EXPECT_CALL(mModel, GetRegistry())
        .WillOnce(ReturnRef(mRegistry));

    auto marker = marker::create(mRegistry,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    marker::setInteractiveRect(marker, { 0.f, 0.f }, { width, height });

    mViewModel.HighlightMarker({ mouse_x, mouse_y });

    auto&& selectable = marker.GetComponent<ol::SelectableComponent>();
    ASSERT_FALSE(selectable.HasBeenEntered());
};

TEST_F(PlotAcquisitionViewModelTests,
       HighlightMarker_InsideInteractiveArea_HasBeenEnteredTrue)
{
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;
    constexpr auto width = 1.f;
    constexpr auto height = 1.f;
    constexpr auto mouse_x = position_x + 0.5f * width;
    constexpr auto mouse_y = position_y + 0.5f * height;

    EXPECT_CALL(mModel, GetRegistry())
        .WillOnce(ReturnRef(mRegistry));

    auto marker = marker::create(mRegistry,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    marker::setInteractiveRect(marker, { 0.f, 0.f }, { width, height });

    mViewModel.HighlightMarker({ mouse_x, mouse_y });

    auto&& selectable = marker.GetComponent<ol::SelectableComponent>();
    ASSERT_TRUE(selectable.HasBeenEntered());
}

TEST_F(PlotAcquisitionViewModelTests,
       SelectMarker_OutOfInteractiveArea_IsSelectedFalse)
{
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;
    constexpr auto width = 1.f;
    constexpr auto height = 1.f;
    constexpr auto mouse_x = position_x + 1.5f * width;
    constexpr auto mouse_y = position_y + 1.5f * height;

    EXPECT_CALL(mModel, GetRegistry())
        .WillOnce(ReturnRef(mRegistry));

    auto marker = marker::create(mRegistry,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    marker::setInteractiveRect(marker, { 0.f, 0.f }, { width, height });

    mViewModel.SelectMarker({ mouse_x, mouse_y });

    auto&& selectable = marker.GetComponent<ol::SelectableComponent>();
    ASSERT_FALSE(selectable.IsSelected());
}

TEST_F(PlotAcquisitionViewModelTests, SelectMarker_InsideBounds_IsSelectedTrue)
{
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;
    constexpr auto width = 1.f;
    constexpr auto height = 1.f;
    constexpr auto mouse_x = position_x + 0.5f * width;
    constexpr auto mouse_y = position_y + 0.5f * height;

    EXPECT_CALL(mModel, GetRegistry())
        .WillOnce(ReturnRef(mRegistry));

    auto marker = marker::create(mRegistry,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    marker::setInteractiveRect(marker, { 0.f, 0.f }, { width, height });

    mViewModel.SelectMarker({ mouse_x, mouse_y });

    auto&& selectable = marker.GetComponent<ol::SelectableComponent>();
    ASSERT_TRUE(selectable.IsSelected());
}

TEST_F(PlotAcquisitionViewModelTests, DeselectMarker)
{
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;
    constexpr auto width = 1.f;
    constexpr auto height = 1.f;
    constexpr auto mouse_x = position_x + 0.5f * width;
    constexpr auto mouse_y = position_y + 0.5f * height;

    EXPECT_CALL(mModel, GetRegistry())
        .WillOnce(ReturnRef(mRegistry));

    auto marker = marker::create(mRegistry,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    marker::setInteractiveRect(marker, { 0.f, 0.f }, { width, height });

    mViewModel.SelectMarker({ mouse_x, mouse_y });
    mViewModel.DeselectMarker();

    auto&& selectable = marker.GetComponent<ol::SelectableComponent>();
    ASSERT_FALSE(selectable.IsSelected());
}

TEST_F(PlotAcquisitionViewModelTests, GetSelectedMarkerLotType)
{
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;
    constexpr auto width = 1.f;
    constexpr auto height = 1.f;
    constexpr auto mouse_x = position_x + 0.5f * width;
    constexpr auto mouse_y = position_y + 0.5f * height;
    constexpr auto type = ol::lot::Type::Begin;

    EXPECT_CALL(mModel, GetRegistry())
        .WillOnce(ReturnRef(mRegistry));

    auto marker = marker::create(mRegistry,
                                 type,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    marker::setInteractiveRect(marker, { 0.f, 0.f }, { width, height });

    mViewModel.SelectMarker({ mouse_x, mouse_y });
    ASSERT_EQ(mViewModel.GetSelectedMarkerLotType(), type);
}

struct TestFeature{};

struct TestPlayfieldSystem final : public ol::System<TestPlayfieldSystem,
                                                    ol::CreatePlotEvent>
{
    bool& create_plot_event_handled;

    TestPlayfieldSystem(bool& _create_plot_event_handled)
        : create_plot_event_handled{ _create_plot_event_handled } {}
};

void systemHandleEvent(TestPlayfieldSystem& system,
                       ol::RegistryRef,
                       const ol::CreatePlotEvent&)
{
    system.create_plot_event_handled = true;
};

TEST_F(PlotAcquisitionViewModelTests, AcquirePlot_CallsHandleEvent)
{
    constexpr auto position_x = 0.f;
    constexpr auto position_y = 0.f;
    constexpr auto width = 1.f;
    constexpr auto height = 1.f;
    constexpr auto mouse_x = position_x + 0.5f * width;
    constexpr auto mouse_y = position_y + 0.5f * height;

    EXPECT_CALL(mModel, GetRegistry())
        .Times(2)
        .WillRepeatedly(ReturnRef(mRegistry));

    bool create_plot_event_handled_flag = false;

    auto feature = mRegistry.AssignFeature<TestFeature>();
    feature.AddSystem<TestPlayfieldSystem>(create_plot_event_handled_flag);

    auto marker = marker::create(mRegistry,
                                 ol::lot::Type::Begin,
                                 true,
                                 mResourceMgr);

    marker::setPosition(marker, { position_x, position_y });
    marker::setInteractiveRect(marker, { 0.f, 0.f }, { width, height });

    auto params = ol::plot::AcquirePlotParams{ ol::plot::TypeId{ 0u } };

    mViewModel.SelectMarker({ mouse_x, mouse_y });
    mViewModel.AcquirePlot(params);

    ASSERT_TRUE(create_plot_event_handled_flag);
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
