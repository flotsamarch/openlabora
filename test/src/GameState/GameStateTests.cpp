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
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "GameState/GameState.hpp"
#include "GameState/ModelMock.hpp"
#include "GameState/GameControllerMock.hpp"
#include "TestApplication.hpp"
#include "GameWindowMock.hpp"
#include "Misc/Matchers.hpp"

namespace test
{

using testing::NiceMock;
using testing::Eq;
using testing::ReturnRef;

using TestResourceManager = NiceMock<ResourceManagerMock>;
using TestModel = NiceMock<ModelMock>;
using TestGameWindow = NiceMock<GameWindowMock>;

template<class TModel>
struct TestViewModel final
{
    using ModelPtr = ol::PtrView<TModel>;
    ModelPtr model;
    TestViewModel(ModelPtr _model)
        : model{ _model }
    {
    }
};

// This view consumes all input except when keyboard button T is down
template<class TViewModel>
struct TestView1 final
{
    using ViewModelPtr = ol::PtrView<TViewModel>;

    ol::ApplicationContext::Ptr app;
    ol::IGameWindow::Ptr window;
    ViewModelPtr view_model;
    bool handle_input_called{ false };
    float update_timer{ 0.f };

    TestView1(ol::ApplicationContext::Ptr _app,
             ol::IGameWindow::Ptr _window,
             ViewModelPtr _view_model)
        : app{ _app },
          window{ _window },
          view_model{ _view_model }
    {
    }

    void Update(float update_delta_seconds)
    {
        update_timer += update_delta_seconds;
    }

    bool HandleInput(ol::Input::PtrConst input)
    {
        handle_input_called = true;
        if (input->IsButtonDown(ol::input::Button::T)) {
            return false;
        }
        return true;
    }
};

// This view never consumes input
template<class TViewModel>
struct TestView2 final
{
    using ViewModelPtr = ol::PtrView<TViewModel>;

    ol::ApplicationContext::Ptr app;
    ol::IGameWindow::Ptr window;
    ViewModelPtr view_model;
    bool handle_input_called{ false };
    float update_timer{ 0.f };

    TestView2(ol::ApplicationContext::Ptr _app,
              ol::IGameWindow::Ptr _window,
              ViewModelPtr _view_model)
        : app{ _app },
          window{ _window },
          view_model{ _view_model }
    {
    }

    void Update(float update_delta_seconds)
    {
        update_timer += update_delta_seconds;
    }

    bool HandleInput(ol::Input::PtrConst)
    { return !(handle_input_called = true); }
};

using TestBinding1 = ol::VVMBinding<TestModel, TestView1, TestViewModel>;
using TestBinding2 = ol::VVMBinding<TestModel, TestView2, TestViewModel>;

class GameStateTests : public ResourceManagerDefaultActionTestBase
{
protected:
    using AppCtx = ol::ApplicationContext;
    using ResMgrPtr = std::shared_ptr<TestResourceManager>;
    using GameWindowPtr = std::shared_ptr<TestGameWindow>;
    using ModelPtr = std::unique_ptr<TestModel>;

    TestApplication mApp{};
    ol::Input mInput{};
    GameWindowPtr mWindow = std::make_shared<TestGameWindow>();
    ol::Registry mRegistry;
    ModelPtr mModel = std::make_unique<TestModel>();

    GameStateTests()
    {
        ON_CALL(*mModel, GetRegistry())
            .WillByDefault(ReturnRef(mRegistry));
    }
};

template<class T>
using NiceGameControllerMock = NiceMock<GameControllerMock<T>>;

using TestGameState = ol::GameState<NiceGameControllerMock,
                                    TestModel,
                                    TestBinding1,
                                    TestBinding2>;

TEST_F(GameStateTests, SetupIntermoduleInteraction)
{
    bool called{ false };
    auto setup = [&called] (const auto&) { called = true; };
    auto game_state = TestGameState{ AppCtx::Ptr{ &mApp },
                                     mWindow,
                                     mResourceMgr,
                                     std::move(mModel),
                                     setup };

    ASSERT_TRUE(called);
}

TEST_F(GameStateTests, HandleInput_All)
{
    auto binding1 = ol::PtrView<TestBinding1>{};
    auto binding2 = ol::PtrView<TestBinding2>{};
    auto setup = [&binding1, &binding2] (TestGameState::VVMBindings& bindings)
    {
        binding1 = ol::PtrView{ &(std::get<TestBinding1>(bindings)) };
        binding2 = ol::PtrView{ &(std::get<TestBinding2>(bindings)) };
    };

    auto game_state = TestGameState{ AppCtx::Ptr{ &mApp },
                                     mWindow,
                                     mResourceMgr,
                                     std::move(mModel),
                                     setup };

    auto event = sf::Event{};
    event.type = sf::Event::KeyPressed;
    event.key.code = sf::Keyboard::T;
    mInput.HandleEvent(event);

    game_state.HandleInput(ol::Input::PtrConst{ &mInput });

    EXPECT_TRUE(binding1->view.handle_input_called);
    ASSERT_TRUE(binding2->view.handle_input_called);
}

TEST_F(GameStateTests, HandleInput_OnlyFirst)
{
    auto binding1 = ol::PtrView<TestBinding1>{};
    auto binding2 = ol::PtrView<TestBinding2>{};
    auto setup = [&binding1, &binding2] (TestGameState::VVMBindings& bindings)
    {
        binding1 = ol::PtrView{ &(std::get<TestBinding1>(bindings)) };
        binding2 = ol::PtrView{ &(std::get<TestBinding2>(bindings)) };
    };

    auto game_state = TestGameState{ AppCtx::Ptr{ &mApp },
                                     mWindow,
                                     mResourceMgr,
                                     std::move(mModel),
                                     setup };

    game_state.HandleInput(ol::Input::PtrConst{ &mInput });

    EXPECT_TRUE(binding1->view.handle_input_called);
    ASSERT_FALSE(binding2->view.handle_input_called);
}

TEST_F(GameStateTests, MapScreenCoordsToWorldCallModelMethod)
{
    const auto new_position = ol::Vector2i{ 77, 836 };

    auto game_state = TestGameState{ AppCtx::Ptr{ &mApp },
                                     mWindow,
                                     mResourceMgr,
                                     std::move(mModel),
                                     [] (const auto&) {} };

    auto&& model = game_state.GetModel();

    EXPECT_CALL(*mWindow, MapScreenToWorldCoords(Eq(new_position)));

    EXPECT_CALL(model, SetWorldMousePosition);

    game_state.MapScreenCoordsToWorld(new_position);
}

TEST_F(GameStateTests, GetWindow)
{
    auto game_state = TestGameState{ AppCtx::Ptr{ &mApp },
                                     mWindow,
                                     mResourceMgr,
                                     std::move(mModel),
                                     [] (const auto&) {} };

    ASSERT_EQ(game_state.GetWindow(), mWindow);
}

TEST_F(GameStateTests, Update_ForwardsCallsToViews)
{
    constexpr auto dt = 4.32f;
    auto timer1 = ol::PtrView<float>{};
    auto timer2 = ol::PtrView<float>{};
    auto setup = [&timer1, &timer2] (TestGameState::VVMBindings& bindings)
    {
        auto&& view1 = std::get<TestBinding1>(bindings).view;
        auto&& view2 = std::get<TestBinding2>(bindings).view;

        timer1.Reset(&view1.update_timer);
        timer2.Reset(&view2.update_timer);
    };
    auto game_state = TestGameState{ AppCtx::Ptr{ &mApp },
                                     mWindow,
                                     mResourceMgr,
                                     std::move(mModel),
                                     setup };

    game_state.Update(dt);

    EXPECT_FLOAT_EQ(*timer1, dt);
    ASSERT_FLOAT_EQ(*timer2, dt);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
