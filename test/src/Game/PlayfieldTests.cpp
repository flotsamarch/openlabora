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
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "Game/Playfield.hpp"
#include "Game/Components/SpriteComponent.hpp"
#include "GameState/Model/Model.hpp"
#include "GameState/Controllers/GCDuel.hpp"
#include "IApplicationMock.hpp"

namespace test
{

namespace ol = open_labora;

using PlayfieldTests = ResourceManagerDefaultActionTestBase;

class PlayfieldEntityTests : public PlayfieldTests
{
    using Model = ol::Model;
    using ControllerPtr = ol::GameController::Ptr;
    using GCDuel = ol::GCDuel;
protected:
    IApplicationMock<ol::StateIdsVariant> mApp;

private:
    using AppPtr = ol::PtrView<ol::IApplication<ol::StateIdsVariant>>;

protected:
    Model::Ptr mModel{ std::make_shared<Model>() };
    ControllerPtr mController{ std::make_shared<GCDuel>(AppPtr(&mApp),
                                                                mResourceMgr,
                                                                mModel) };
    ol::Playfield::Ptr mPlayfield = ol::playfield::create(mResourceMgr, {});
};

static constexpr auto zero_init_x = 0.f;
static constexpr auto zero_init_y = 0.f;
static constexpr auto non_zero_init_x = 154.f;
static constexpr auto non_zero_init_y = 38.f;

TEST_F(PlayfieldTests, FactoryFunctions_VectorDefault)
{
    auto pf = ol::playfield::create(mResourceMgr, {});
    auto&& sprite = ol::ecs::getComponent<ol::SpriteComponent>(*pf);
    const auto position = sprite.GetPosition();

    EXPECT_FLOAT_EQ(0.f, position.x);
    ASSERT_FLOAT_EQ(0.f, position.y);
}

TEST_F(PlayfieldTests, FactoryFunctions_VectorNonZero)
{
    auto pf = ol::playfield::create(mResourceMgr,
                                    {non_zero_init_x, non_zero_init_y});
    auto&& sprite = ol::ecs::getComponent<ol::SpriteComponent>(*pf);
    const auto position = sprite.GetPosition();

    EXPECT_FLOAT_EQ(non_zero_init_x, position.x);
    ASSERT_FLOAT_EQ(non_zero_init_y, position.y);
}

TEST_F(PlayfieldTests, FactoryFunctions_FloatsZero)
{
    auto pf = ol::playfield::create(mResourceMgr, zero_init_x, zero_init_y);
    auto&& sprite = ol::ecs::getComponent<ol::SpriteComponent>(*pf);
    const auto position = sprite.GetPosition();

    EXPECT_FLOAT_EQ(zero_init_x, position.x);
    ASSERT_FLOAT_EQ(zero_init_y, position.y);
}

TEST_F(PlayfieldTests, FactoryFunctions_FloatsNonZero)
{
    auto pf = ol::playfield::create(mResourceMgr,
                                    non_zero_init_x,
                                    non_zero_init_y);
    auto&& sprite = ol::ecs::getComponent<ol::SpriteComponent>(*pf);
    const auto position = sprite.GetPosition();

    EXPECT_FLOAT_EQ(non_zero_init_x, position.x);
    ASSERT_FLOAT_EQ(non_zero_init_y, position.y);
}

TEST_F(PlayfieldEntityTests, EventHandling)
{
    auto event = sf::Event{};
    ASSERT_FALSE(entityHandleEvent(mPlayfield, mController, event));
}

TEST_F(PlayfieldEntityTests, Update)
{
    using TCC = ol::TextureContainerComponent;
    entityUpdate(mPlayfield, mController, 0.f);

    auto&& texture_component = ol::ecs::getComponent<TCC>(*mPlayfield);

    EXPECT_FALSE(texture_component.NeedsUpdate());
    EXPECT_EQ(mModel->GetDrawableObjects().GetSize(), 1);
}

TEST(PlayfieldFunctions, GetPlotStripXOffset_FirstZero)
{
    ASSERT_EQ(ol::playfield::getPlotStripXOffset(ol::plot::Type::Begin), 0);
}

TEST(PlayfieldFunctions, GetPlotStripXOffset_NonFirstNonZero)
{
    using PlotType = ol::plot::Type;
    for (auto&& type = PlotType::Begin + 1; type != PlotType::End; ++type) {
        ASSERT_GT(ol::playfield::getPlotStripXOffset(type), 0);
    }
}

TEST(PlayfieldFunctions, GetPlotStripXOffset_NextAlwaysGreater)
{
    using PlotType = ol::plot::Type;
    auto prev{ 0 };
    for (auto&& type = PlotType::Begin + 1; type != PlotType::End; ++type) {
        auto cur = ol::playfield::getPlotStripXOffset(type);
        EXPECT_GT(cur, prev);
        EXPECT_GE(cur - prev, ol::tile::kTileWidth);
        prev = cur;
    }
}

} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
