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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "GameState/MainMenuFwd.hpp"
#include "GameState/MainMenu.hpp"
#include "TestApplication.hpp"
#include "GameWindowMock.hpp"
#include "Resource/ResourceManagerMock.hpp"

namespace test
{

namespace ol = open_labora;

using testing::NiceMock;
using testing::_;

using TestWindow = NiceMock<GameWindowMock>;
using TestResourceMgr = NiceMock<ResourceManagerMock>;

namespace
{

tgui::GuiSFML _gui; // Required to create GUI objects

} // namespace anonymous

class MainMenuTests : public testing::Test
{
    using WinPtr = std::shared_ptr<TestWindow>;
    using ResMgrPtr = std::shared_ptr<TestResourceMgr>;

protected:
    using CtxPtr = ol::ApplicationContext::Ptr;

    TestApplication mApp{};
    WinPtr mWindow = std::make_shared<TestWindow>();
    ResMgrPtr mResourceMgr = std::make_shared<TestResourceMgr>();
};

TEST_F(MainMenuTests, Constructor_AddsWidgetToWindow)
{
    EXPECT_CALL(*mWindow, AddWidget(_));

    auto state = ol::MainMenu{ CtxPtr{ &mApp }, mWindow, mResourceMgr };
}

TEST_F(MainMenuTests, GetFlagIsFinal_False)
{
    auto state = ol::MainMenu{ CtxPtr{ &mApp }, mWindow, mResourceMgr };

    ASSERT_FALSE(ol::stateGetFlagIsFinal(state));
}

TEST_F(MainMenuTests, GetDrawableObjects_HasNone)
{
    auto state = ol::MainMenu{ CtxPtr{ &mApp }, mWindow, mResourceMgr };

    ASSERT_TRUE(ol::stateGetDrawableObjects(state).IsEmpty());
}

TEST_F(MainMenuTests, StateHandleInput_EscapeChangesStateToFinal)
{
    auto state = ol::MainMenu{ CtxPtr{ &mApp }, mWindow, mResourceMgr };
    auto input = ol::Input{};
    auto event = sf::Event{};
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::Escape;

    input.HandleEvent(event);
    ol::stateHandleInput(state, ol::Input::PtrConst{ &input });

    ASSERT_TRUE(stateGetFlagIsFinal(mApp.GetState()));
}

// stateUpdate has no body and requires no testing

TEST_F(MainMenuTests, ChangeState)
{
    ol::state::changeState(ol::state::MainMenu{},
                           CtxPtr{ &mApp },
                           mWindow,
                           mResourceMgr);

    ASSERT_FALSE(stateGetFlagIsFinal(mApp.GetState()));
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
