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
#include "GameState/GameController.hpp"
#include "GameState/ModelMock.hpp"
#include "Resource/ResourceManagerMock.hpp"
#include "TestApplication.hpp"
#include "Input/Input.hpp"
#include "Misc/Matchers.hpp"

namespace test
{

using testing::Eq;
using testing::NiceMock;

using TestResourceManager = NiceMock<ResourceManagerMock>;
using TestModel = NiceMock<ModelMock>;

class GameControllerTests : public testing::Test
{
protected:
    using AppCtx = ol::ApplicationContext;
    using ResMgrPtr = std::shared_ptr<TestResourceManager>;
    using GameController = ol::GameController<TestModel>;

    TestApplication mApp{};
    ResMgrPtr mResourceMgr = std::make_shared<TestResourceManager>();
    TestModel mModel{};
    ol::Input mInput{};
};

TEST_F(GameControllerTests, Construction) // TODO actual testing
{
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    ASSERT_TRUE(true);
}

TEST_F(GameControllerTests, HandleInput) // TODO actual testing
{
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    controller.HandleInput(ol::Input::PtrConst{ &mInput });

    ASSERT_TRUE(true);
}

TEST_F(GameControllerTests, Update) // TODO actual testing
{
    constexpr auto delta = 1.f;
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    controller.Update(delta);

    ASSERT_TRUE(true);
}

TEST_F(GameControllerTests, SetPaused_Pause)
{
    bool paused{ true };
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    EXPECT_CALL(mModel, SetPaused(Eq(paused)));

    controller.SetPaused(paused);
}

TEST_F(GameControllerTests, SetPaused_Unpause)
{
    bool paused{ false };
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    EXPECT_CALL(mModel, SetPaused(Eq(paused)));

    controller.SetPaused(paused);
}

TEST_F(GameControllerTests, GetModel)
{
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    ASSERT_EQ(controller.GetModel().Get(), &mModel);
}

TEST_F(GameControllerTests, GetResourceManager)
{
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    ASSERT_EQ(controller.GetResourceManager(), mResourceMgr);
}

TEST_F(GameControllerTests, SetWorldMousePositionCallsModelMethod)
{
    const auto new_position = ol::Vector2f{ 74.f, 839.f };
    auto controller = GameController{ AppCtx::Ptr{ &mApp },
                                      mResourceMgr,
                                      ModelMock::Ptr{ &mModel },
                                      0 };

    EXPECT_CALL(mModel, SetWorldMousePosition(Vector2fEq(new_position)));

    controller.SetWorldMousePosition(new_position);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
