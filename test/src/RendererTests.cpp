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
#include <SFML/Window/Event.hpp>
#include "RendererDependenciesMocks.hpp"
#include "Renderer.hpp"
#include "Misc/PtrView.hpp"

namespace test
{

namespace ol = open_labora;

using testing::NiceMock;

using TestWindow = NiceMock<WindowMock>;
using TestGui = NiceMock<GuiMock<TestWindow>>;

using Renderer = ol::Renderer<NiceMock<GuiMock<TestWindow>>, TestWindow>;

using testing::Return;
using testing::_;
using testing::Field;

class TestFRenderer : public testing::Test
{
protected:
    TestGui mGui;
    TestWindow mWindow;
    Renderer mRenderer{ ol::PtrView{ &mGui }, ol::PtrView{ &mWindow } };
public:
    virtual ~TestFRenderer() {};
};

TEST_F(TestFRenderer, PollEventTest)
{
    ON_CALL(mWindow, isOpen)
        .WillByDefault(Return(true));

    EXPECT_CALL(mWindow, pollEvent(_))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    EXPECT_EQ(mRenderer.PollEvent(), std::nullopt);
    ASSERT_NE(mRenderer.PollEvent(), std::nullopt);
}

TEST_F(TestFRenderer, IsWindowOpen)
{
    EXPECT_CALL(mWindow, isOpen())
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(false)); // Will also be called in destructor

    EXPECT_NO_FATAL_FAILURE(mRenderer.IsWindowOpen());
    ASSERT_NO_FATAL_FAILURE(mRenderer.IsWindowOpen());
}

TEST_F(TestFRenderer, Clear)
{
    EXPECT_CALL(mWindow, clear());

    ASSERT_NO_FATAL_FAILURE(mRenderer.Clear());
}

TEST_F(TestFRenderer, Draw)
{
    constexpr auto range_size = 5;
    auto sprites = std::vector<ol::Sprite>{ range_size };
    auto range = ol::DrawableContainer{};

    for (auto&& sprite : sprites) {
        range.push_back(std::ref(sprite));
    }

    EXPECT_CALL(mWindow, draw(_))
        .Times(range_size);

    ASSERT_NO_FATAL_FAILURE(mRenderer.Draw({ range }));
}

TEST_F(TestFRenderer, Display)
{
    EXPECT_CALL(mWindow, display());
    EXPECT_CALL(mGui, draw());

    ASSERT_NO_FATAL_FAILURE(mRenderer.Display());
}

TEST_F(TestFRenderer, HandleEvent)
{
    EXPECT_CALL(mGui, handleEvent(_))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    sf::Event event;

    EXPECT_FALSE(mRenderer.HandleEvent(event));
    ASSERT_TRUE(mRenderer.HandleEvent(event));
}

TEST_F(TestFRenderer, HandleEventCloseWindow)
{
    sf::Event event;
    event.type = sf::Event::Closed;

    const auto matcher = Field(&sf::Event::type, event.type);

    EXPECT_CALL(mGui, handleEvent(matcher))
        .WillOnce(Return(false));

    EXPECT_CALL(mWindow, close());

    ASSERT_FALSE(mRenderer.HandleEvent(event));
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
