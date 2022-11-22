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
#include <TGUI/Backends/SFML.hpp>
#include "GUI/PlotAcquisitionMenu.hpp"
#include "RendererDependenciesMocks.hpp"
#include "GameWindowMock.hpp"

namespace test
{

namespace ol = open_labora;

constexpr auto win_size_x{ 1920 };
constexpr auto win_size_y{ 1080 };

namespace
{

tgui::GuiSFML _gui; // Required to create GUI objects

} // namespace anonymous

class PlotAcquisitionMenuTests : public ::testing::Test
{
    using WindowMock = sf::RenderTexture;
    using Gui = tgui::GuiSFML;
    using TestWindow = testing::NiceMock<GameWindowMock>;
    using TestWindowPtr = std::shared_ptr<TestWindow>;

    WindowMock mWindow{};

protected:
    using MenuWindowId = ol::plot_acquisition::MenuWindowId;

    Gui mGui{};
    TestWindowPtr mGameWindow = std::make_shared<TestWindow>();
    ol::PlotAcquisitionMenu mPlotAcquisitionMenu{};

    PlotAcquisitionMenuTests()
    {
        mWindow.create(win_size_x, win_size_y);
        mGui.setTarget(mWindow);
    }
};

TEST_F(PlotAcquisitionMenuTests, IsVisible_FalseWhenNoWindows)
{
    ASSERT_FALSE(mPlotAcquisitionMenu.IsVisible(MenuWindowId::Begin));
}

TEST_F(PlotAcquisitionMenuTests, IsVisible_FalseWhenWindowNotShown)
{
    constexpr auto window_id = MenuWindowId::Begin;

    auto window = ol::ConfirmationWindow{ mGameWindow, 1, 1 };
    window.Show(false);

    mPlotAcquisitionMenu.Emplace(window_id, std::move(window));

    ASSERT_FALSE(mPlotAcquisitionMenu.IsVisible(MenuWindowId::Begin));
}

TEST_F(PlotAcquisitionMenuTests, IsVisible_FalseAfterWindowIsHiddenDuringEmplace)
{
    constexpr auto window_id = MenuWindowId::Begin;

    auto window = ol::ConfirmationWindow{ mGameWindow, 1, 1 };
    window.Show();

    mPlotAcquisitionMenu.Emplace(window_id, std::move(window));

    ASSERT_FALSE(mPlotAcquisitionMenu.IsVisible(MenuWindowId::Begin));
}

TEST_F(PlotAcquisitionMenuTests, IsVisible_FalseWhenOtherWindowShown)
{
    constexpr auto shown_id = MenuWindowId::Confirm;
    constexpr auto hidden_id = MenuWindowId::ChooseOne;

    auto window_1 = ol::ConfirmationWindow{ mGameWindow, 1, 1 };
    auto window_2 = ol::ConfirmationWindow{ mGameWindow, 1, 1 };

    mPlotAcquisitionMenu.Emplace(shown_id, std::move(window_1));
    mPlotAcquisitionMenu.Emplace(hidden_id, std::move(window_2));

    mPlotAcquisitionMenu.Show(shown_id);

    ASSERT_FALSE(mPlotAcquisitionMenu.IsVisible(hidden_id));
}

TEST_F(PlotAcquisitionMenuTests, IsVisible_False_HiddenWhenOtherWindowGetsShown)
{
    constexpr auto shown_id = MenuWindowId::Confirm;
    constexpr auto hidden_id = MenuWindowId::ChooseOne;

    auto window_1 = ol::ConfirmationWindow{ mGameWindow, 1, 1 };
    auto window_2 = ol::ConfirmationWindow{ mGameWindow, 1, 1 };

    mPlotAcquisitionMenu.Emplace(shown_id, std::move(window_1));
    mPlotAcquisitionMenu.Emplace(hidden_id, std::move(window_2));

    mPlotAcquisitionMenu.Show(hidden_id);
    mPlotAcquisitionMenu.Show(shown_id);

    ASSERT_FALSE(mPlotAcquisitionMenu.IsVisible(hidden_id));
}

TEST_F(PlotAcquisitionMenuTests, IsVisible_TrueWhenShown)
{
    constexpr auto state = MenuWindowId::Begin;

    auto window = ol::ConfirmationWindow{ mGameWindow, 1, 1 };

    mPlotAcquisitionMenu.Emplace(state, std::move(window));
    mPlotAcquisitionMenu.Show(state);

    ASSERT_TRUE(mPlotAcquisitionMenu.IsVisible(state));
}

TEST_F(PlotAcquisitionMenuTests, IsVisible_False_HideCurrentlyVisible)
{
    constexpr auto state = MenuWindowId::Begin;

    auto window = ol::ConfirmationWindow{ mGameWindow, 1, 1 };

    mPlotAcquisitionMenu.Emplace(state, std::move(window));
    mPlotAcquisitionMenu.Show(state);
    mPlotAcquisitionMenu.HideCurrentlyVisible();

    ASSERT_FALSE(mPlotAcquisitionMenu.IsVisible(state));
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
