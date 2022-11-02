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
#include "ECS/MassAssignComponents.hpp"
#include "Game/Components/LotDequeComponent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/DynamicTextureComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"

namespace open_labora
{

namespace lot_deque
{

Entity create(RegistryRef registry,
              lot::Type type,
              const Vector2f& position)
{
    auto entity = registry.CreateEntity();
    MassAssignComponents{ entity }
        .Assign<LotDequeComponent>(type)
        .Assign<PositionComponent>(position.x, position.y)
        .Assign<DynamicTextureComponent>()
        .Assign<SpriteComponent>();

    return entity;
}

} // namespace lot_deque

} // namespace open_labora
