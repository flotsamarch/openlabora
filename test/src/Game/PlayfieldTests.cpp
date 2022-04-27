#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Resource/IResourceManagerMock.hpp"
#include "Game/Playfield.hpp"
#include "Game/Components/SpriteComponent.hpp"
#include "GameState/Model/Model.hpp"
#include "GameState/Controllers/GCDuel.hpp"
#include "IApplicationMock.hpp"

namespace Test
{

using ResManagerPtr = IResourceManagerMock::Ptr;
using ::OpenLabora::playfield::create;
using ::OpenLabora::playfield::Playfield;
using ::OpenLabora::ecs::getComponent;
using ::OpenLabora::PtrView;
using PlayfieldPtr = std::shared_ptr<Playfield>;
using ::testing::Return;

class PlayfieldTests : public ::testing::Test
{
protected:
    ResManagerPtr mResManager{ std::make_shared<IResourceManagerMock>() };
    sf::Texture mTexture{};

public:
    PlayfieldTests()
    {
        ON_CALL(*mResManager, GetTexture)
            .WillByDefault(Return(mTexture));
    }
};

class PlayfieldEntityTests : public PlayfieldTests
{
    using Model = ::OpenLabora::Model;
    using ControllerPtr = ::OpenLabora::GameController::Ptr;
    using GCDuel = ::OpenLabora::GCDuel;
protected:
    IApplicationMock<OpenLabora::StateIdsVariant> mApp;

private:
    using AppPtr = PtrView<OpenLabora::IApplication<OpenLabora::StateIdsVariant>>;

protected:
    Model::Ptr mModel{ std::make_shared<Model>() };
    ControllerPtr mController{ std::make_shared<GCDuel>(AppPtr(&mApp),
                                                                mResManager,
                                                                mModel) };
    PlayfieldPtr mPlayfield = create(mResManager, {});
};

static constexpr auto zero_init_x = 0.f;
static constexpr auto zero_init_y = 0.f;
static constexpr auto non_zero_init_x = 154.f;
static constexpr auto non_zero_init_y = 38.f;

TEST_F(PlayfieldTests, FactoryFunctions_VectorDefault)
{
    auto pf = create(mResManager, {});
    auto&& sprite = getComponent<OpenLabora::SpriteComponent>(*pf);
    const auto position = sprite.GetPosition();

    EXPECT_FLOAT_EQ(0.f, position.x);
    ASSERT_FLOAT_EQ(0.f, position.y);
}

TEST_F(PlayfieldTests, FactoryFunctions_VectorNonZero)
{
    auto pf = create(mResManager, {non_zero_init_x, non_zero_init_y});
    auto&& sprite = getComponent<OpenLabora::SpriteComponent>(*pf);
    const auto position = sprite.GetPosition();

    EXPECT_FLOAT_EQ(non_zero_init_x, position.x);
    ASSERT_FLOAT_EQ(non_zero_init_y, position.y);
}

TEST_F(PlayfieldTests, FactoryFunctions_FloatsZero)
{
    auto pf = create(mResManager, zero_init_x, zero_init_y);
    auto&& sprite = getComponent<OpenLabora::SpriteComponent>(*pf);
    const auto position = sprite.GetPosition();

    EXPECT_FLOAT_EQ(zero_init_x, position.x);
    ASSERT_FLOAT_EQ(zero_init_y, position.y);
}

TEST_F(PlayfieldTests, FactoryFunctions_FloatsNonZero)
{
    auto pf = create(mResManager, non_zero_init_x, non_zero_init_y);
    auto&& sprite = getComponent<OpenLabora::SpriteComponent>(*pf);
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
    using TCC = OpenLabora::TextureContainerComponent;
    entityUpdate(mPlayfield, 0.f, mController);

    auto&& texture_component = getComponent<TCC>(*mPlayfield);

    EXPECT_FALSE(texture_component.NeedsUpdate());
    EXPECT_EQ(mModel->GetDrawableObjects().GetSize(), 1);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
