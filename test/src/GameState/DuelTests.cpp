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
#include "GameState/DuelFwd.hpp"
#include "GameState/Duel.hpp"
#include "TestApplication.hpp"
#include "GameWindowMock.hpp"
#include "Resource/ResourceManagerMock.hpp"
#include "GameState/ModelMock.hpp"

namespace test
{

namespace ol = open_labora;

using testing::NiceMock;
using testing::Return;

using TestWindow = NiceMock<GameWindowMock>;
using TestResourceMgr = NiceMock<ResourceManagerMock>;

namespace
{

tgui::GuiSFML _gui; // Required to create GUI objects

} // namespace anonymous

class DuelTests : public testing::Test
{
    using WinPtr = std::shared_ptr<TestWindow>;
    using ResMgrPtr = std::shared_ptr<TestResourceMgr>;

protected:
    using CtxPtr = ol::ApplicationContext::Ptr;

    TestApplication mApp{};
    WinPtr mWindow = std::make_shared<TestWindow>();
    ResMgrPtr mResourceMgr = std::make_shared<TestResourceMgr>();
    std::function<void(ol::Duel::VVMBindings)> mSetup = [] (const auto&) {};
    std::unique_ptr<ol::Model> mModel{ std::make_unique<ol::Model>() };
};

TEST_F(DuelTests, GetFlagIsFinal_False)
{
    auto state = ol::Duel{ CtxPtr{ &mApp },
                           mWindow,
                           mResourceMgr,
                           std::move(mModel),
                           mSetup };

    ASSERT_FALSE(ol::stateGetFlagIsFinal(state));
}

TEST_F(DuelTests, GetDrawableObjects_NotEmpty)
{
    constexpr auto sprite_count{ 5u };
    auto sprites = std::vector<ol::Sprite>{ sprite_count };

    for (auto&& sprite : sprites) {
        mModel->AddDrawableObject(sprite);
    }

    auto state = ol::Duel{ CtxPtr{ &mApp },
                           mWindow,
                           mResourceMgr,
                           std::move(mModel),
                           mSetup };

    ASSERT_EQ(ol::stateGetDrawableObjects(state).GetSize(), sprite_count);
}

TEST_F(DuelTests, StateHandleInput_MouseMoveUpdatesWorldMousePosition)
{
    constexpr auto new_pos_x = 3702.f;
    constexpr auto new_pos_y = 90560.f;
    auto state = ol::Duel{ CtxPtr{ &mApp },
                           mWindow,
                           mResourceMgr,
                           std::move(mModel),
                           mSetup };
    auto input = ol::Input{};
    auto&& model = state.GetModel();
    auto event = sf::Event{};
    event.type = sf::Event::MouseMoved;
    event.mouseMove.x = 0;
    event.mouseMove.y = 0;

    EXPECT_CALL(*mWindow, MapScreenToWorldCoords)
        .WillOnce(Return(ol::Vector2f{ new_pos_x, new_pos_y }));

    input.HandleEvent(event);
    ol::stateHandleInput(state, ol::Input::PtrConst{ &input });

    auto pos = model.GetWorldMousePosition();

    EXPECT_FLOAT_EQ(pos.x, new_pos_x);
    ASSERT_FLOAT_EQ(pos.y, new_pos_y);
}

// stateUpdate has no body and requires no testing

TEST_F(DuelTests, ChangeState)
{
    ol::state::changeState(ol::state::Duel{},
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
