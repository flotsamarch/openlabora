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
#include "GameState/Views/PlotAcquisitionView.hpp"
#include "GameState/ViewModels/PlotAcquisitionViewModelMock.hpp"
#include "Input/Input.hpp"
#include "GameWindowMock.hpp"
#include "GameState/ModelMock.hpp"
#include "Misc/Matchers.hpp"

namespace test
{

namespace pa = ol::plot_acquisition;

using testing::NiceMock;
using testing::Return;

using TestGameWindow = NiceMock<GameWindowMock>;
using TestGameWindowPtr = std::shared_ptr<TestGameWindow>;

using TestModel = NiceMock<ModelMock>;
using TestViewModel = NiceMock<PlotAcquisitionViewModelMock>;
using TestPlotAcquisitionView = ol::PlotAcquisitionView<TestViewModel>;

namespace
{

tgui::GuiSFML _gui; // Required to create GUI objects

} // namespace anonymous

class PlotAcquisitionViewTests : public testing::Test
{
protected:
    using WinPtr = ol::IGameWindow::Ptr;

    TestModel mModel{};
    TestViewModel mViewModel{};
    ol::ApplicationContext::Ptr mApp{};
    TestGameWindowPtr mGameWindow = std::make_shared<TestGameWindow>();
    ol::Input mInput{};
    pa::ButtonToPlotTypeIdMap mButtonToTypeIdMap;

    pa::CreateWindowParams mParams{ mButtonToTypeIdMap };

    std::function<void()> mNoOp = [] {};
    ol::plot::AcquireCallback mDefaultAcquire = [] (const auto&) {};

    PlotAcquisitionViewTests() { mParams.game_window = mGameWindow; }
};

TEST_F(PlotAcquisitionViewTests, CreateWindowConfirm_ReturnsConfirmId)
{
    auto result = pa::createWindowConfirm(mParams);

    ASSERT_EQ(result.id, pa::MenuWindowId::Confirm);
}

TEST_F(PlotAcquisitionViewTests, CreateWindowChooseOne_ReturnsChooseOneId)
{
    auto result = pa::createWindowChooseOne(mParams);

    ASSERT_EQ(result.id, pa::MenuWindowId::ChooseOne);
}

TEST_F(PlotAcquisitionViewTests, CreateWindowChooseOne_FillsButtonToIdMap)
{
    pa::createWindowChooseOne(mParams);

    ASSERT_EQ(mButtonToTypeIdMap.size(), 2);
}

TEST_F(PlotAcquisitionViewTests, WindowConfirm_Confirm_HidesWindow)
{
    bool hidden_flag = false;
    auto hide_window_callback = [&flag = hidden_flag] { flag = true; };

    mParams.hide_visible_callback = std::move(hide_window_callback);
    mParams.acquire_plot_callback = mDefaultAcquire;
    auto result = pa::createWindowConfirm(mParams);

    result.window.Confirm();

    ASSERT_TRUE(hidden_flag);
}

TEST_F(PlotAcquisitionViewTests, WindowConfirm_Confirm_AcquiresPlot)
{
    bool acquired_flag = false;
    auto acquire_plot_callback =
    [&flag = acquired_flag] (const ol::plot::AcquirePlotParams&)
    { flag = true; };

    mParams.acquire_plot_callback = std::move(acquire_plot_callback);
    mParams.hide_visible_callback = mNoOp;
    auto result = pa::createWindowConfirm(mParams);

    result.window.Confirm();

    ASSERT_TRUE(acquired_flag);
}

TEST_F(PlotAcquisitionViewTests, WindowConfirm_Decline_HidesWindow)
{
    bool hidden_flag = false;
    auto hide_window_callback = [&flag = hidden_flag] { flag = true; };

    mParams.decline_action = std::move(hide_window_callback);
    auto result = pa::createWindowConfirm(mParams);

    result.window.Decline();

    ASSERT_TRUE(hidden_flag);
}

TEST_F(PlotAcquisitionViewTests, WindowChooseOne_Confirm_HidesWindow)
{
    bool hidden_flag = false;
    auto hide_window_callback = [&flag = hidden_flag] { flag = true; };

    mParams.hide_visible_callback = std::move(hide_window_callback);
    mParams.acquire_plot_callback = mDefaultAcquire;
    auto result = pa::createWindowChooseOne(mParams);
    mButtonToTypeIdMap.begin()->first->setChecked(true);

    result.window.Confirm();

    ASSERT_TRUE(hidden_flag);
}

TEST_F(PlotAcquisitionViewTests, WindowChooseOne_Confirm_AcquiresPlot)
{
    bool acquired_flag = false;
    auto acquire_plot_callback =
    [&flag = acquired_flag] (const auto&) { flag = true; };

    mParams.acquire_plot_callback = std::move(acquire_plot_callback);
    mParams.hide_visible_callback = mNoOp;
    auto result = pa::createWindowChooseOne(mParams);
    mButtonToTypeIdMap.begin()->first->setChecked(true);

    result.window.Confirm();

    ASSERT_TRUE(acquired_flag);
}

TEST_F(PlotAcquisitionViewTests, WindowChooseOne_Decline_HidesWindow)
{
    bool hidden_flag = false;
    auto hide_window_callback = [&flag = hidden_flag] { flag = true; };

    mParams.decline_action = std::move(hide_window_callback);
    auto result = pa::createWindowChooseOne(mParams);

    result.window.Decline();

    ASSERT_TRUE(hidden_flag);
}

TEST_F(PlotAcquisitionViewTests, Ctor_CreatesAllWindows)
{
    auto view = TestPlotAcquisitionView
    {
        mApp,
        mGameWindow,
        ol::PtrView{ &mViewModel }
    };

    ASSERT_EQ(view.GetWindowCount(), 2);
}

TEST_F(PlotAcquisitionViewTests, HandleInput_MouseMoving_HighlightMarkerCalled)
{
    const auto mouse_pos = ol::Vector2f{ 38.f, 968.f };

    EXPECT_CALL(*mGameWindow, MapScreenToWorldCoords)
        .WillOnce(Return(mouse_pos));

    EXPECT_CALL(mViewModel, HighlightMarker(Vector2fEq(mouse_pos)))
                .Times(1);

    auto event = sf::Event{};
    event.type = sf::Event::MouseMoved;
    mInput.HandleEvent(event);

    auto view = TestPlotAcquisitionView
    {
        mApp,
        mGameWindow,
        ol::PtrView{ &mViewModel }
    };

    ASSERT_FALSE(view.HandleInput(ol::Input::PtrConst{ &mInput }));
}

TEST_F(PlotAcquisitionViewTests,
       HandleInput_MouseReleased_SelectMarkerReturnsFalse)
{
    const auto mouse_pos = ol::Vector2f{ 38.f, 968.f };

    EXPECT_CALL(*mGameWindow, MapScreenToWorldCoords)
        .WillOnce(Return(mouse_pos));

    EXPECT_CALL(mViewModel, SelectMarker(Vector2fEq(mouse_pos)))
        .WillOnce(Return(false));

    EXPECT_CALL(mViewModel, GetSelectedMarkerLotType())
        .Times(0);

    auto event = sf::Event{};
    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    mInput.HandleEvent(event);

    auto view = TestPlotAcquisitionView
    {
        mApp,
        mGameWindow,
        ol::PtrView{ &mViewModel }
    };

    ASSERT_FALSE(view.HandleInput(ol::Input::PtrConst{ &mInput }));
}

TEST_F(PlotAcquisitionViewTests,
       HandleInput_MouseReleased_SelectMarkerReturnsTrue_MenuIsVisible)
{
    constexpr auto lot_type = ol::lot::Type::Begin;

    const auto mouse_pos = ol::Vector2f{ 38.f, 968.f };

    EXPECT_CALL(*mGameWindow, MapScreenToWorldCoords)
        .WillOnce(Return(mouse_pos));

    EXPECT_CALL(mViewModel, SelectMarker(Vector2fEq(mouse_pos)))
        .WillOnce(Return(true));

    EXPECT_CALL(mViewModel, GetSelectedMarkerLotType())
        .WillOnce(Return(lot_type));

    auto event = sf::Event{};
    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    mInput.HandleEvent(event);

    auto view = TestPlotAcquisitionView
    {
        mApp,
        mGameWindow,
        ol::PtrView{ &mViewModel }
    };
    view.HandleInput(ol::Input::PtrConst{ &mInput });

    ASSERT_TRUE(view.GetMenu().IsVisible(pa::MenuWindowId::Confirm));
}

//HandleInput_MouseButtonReleased_Deselectedmarker

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
