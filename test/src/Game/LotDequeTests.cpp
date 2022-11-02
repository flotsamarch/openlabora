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

#include "Game/LotDeque.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "Game/Components/LotDequeComponent.hpp"
#include "Game/Components/DynamicTextureComponent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"

namespace test
{

namespace ld = ol::lot_deque;
namespace lot = ol::lot;

constexpr auto kLotType = lot::Type::Begin;
constexpr auto kCentral = lot::Type::Central;

class LotDequeTests : public ResourceManagerDefaultActionTestBase
{
protected:
    ol::Registry mRegistry;
    ol::RegistryRef mRegistryRef{ mRegistry };
};

TEST_F(LotDequeTests, Create_AddsEntityToRegistry)
{
    ld::create(mRegistryRef, kLotType, { 0.f, 0.f });

    ASSERT_NE(mRegistry.EntityCount(), 0);
}

TEST_F(LotDequeTests, Create_EntityHasLotDequeComponent)
{
    auto deque = ld::create(mRegistryRef, kLotType, { 0.f, 0.f });

    ASSERT_NE(deque.FindComponent<ol::LotDequeComponent>(), nullptr);
}

TEST_F(LotDequeTests, Create_EntityHasPositionComponent)
{
    auto deque = ld::create(mRegistryRef, kLotType, { 0.f, 0.f });

    ASSERT_NE(deque.FindComponent<ol::PositionComponent>(), nullptr);
}

TEST_F(LotDequeTests, Create_EntityHasDynamicTextureComponent)
{
    auto deque = ld::create(mRegistryRef, kLotType, { 0.f, 0.f });

    ASSERT_NE(deque.FindComponent<ol::DynamicTextureComponent>(), nullptr);
}

TEST_F(LotDequeTests, Create_EntityHasSpriteComponent)
{
    auto deque = ld::create(mRegistryRef, kLotType, { 0.f, 0.f });

    ASSERT_NE(deque.FindComponent<ol::SpriteComponent>(), nullptr);
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
