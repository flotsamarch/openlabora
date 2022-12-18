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

#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <ecs.hpp/ecs.hpp>
#include "Misc/PtrView.hpp"

namespace open_labora
{

using EntityId = ecs_hpp::entity_id;

class Entity final
{
    using LibEntity = ecs_hpp::entity;
    LibEntity mEntity;

public:
    Entity(LibEntity entity) noexcept
        : mEntity{ entity } {}

    EntityId GetId() const noexcept
    { return mEntity.id(); }

    Entity Clone() const
    { return { mEntity.clone() }; }

    void Destroy() noexcept
    { mEntity.destroy(); }

    bool IsValid() const noexcept
    { return mEntity.valid(); }

    template<class TComponent, class... Args>
    TComponent& AssignComponent(Args&&... args)
    { return mEntity.assign_component<TComponent>(std::forward<Args>(args)...); }

    template<class TComponent, class... Args>
    TComponent& GetOrCreateComponent(Args&&... args)
    { return mEntity.ensure_component<TComponent>(std::forward<Args>(args)...); }

    template<class TComponent>
    bool HasComponent() const noexcept
    { return mEntity.exists_component<TComponent>(); }

    template<class TComponent>
    bool RemoveComponent() noexcept
    { return mEntity.remove_component<TComponent>(); }

    int RemoveAllComponents() noexcept
    { return static_cast<int>(mEntity.remove_all_components()); }

    template<class TComponent>
    TComponent& GetComponent()
    { return mEntity.get_component<TComponent>(); }

    template<class TComponent>
    const TComponent& GetComponent() const
    { return mEntity.get_component<TComponent>(); }

    template<class TComponent>
    PtrView<TComponent> FindComponent() noexcept
    { return PtrView<TComponent>{ mEntity.find_component<TComponent>() }; }

    template<class TComponent>
    PtrView<const TComponent> FindComponent() const noexcept
    { return PtrView<const TComponent>{ mEntity.find_component<TComponent>() }; }

    int GetComponentCount() const noexcept
    { return static_cast<int>(mEntity.component_count()); }
};

class ConstEntity final
{
    ecs_hpp::const_entity mEntity;

public:
    ConstEntity(ecs_hpp::const_entity entity)
        : mEntity{ entity } {}

    EntityId GetId() const noexcept
    { return mEntity.id(); }

    bool IsValid() const noexcept
    { return mEntity.valid(); }

    template<class TComponent>
    bool HasComponent() const noexcept
    { return mEntity.exists_component<TComponent>(); }

    template<class TComponent>
    const TComponent& GetComponent() const noexcept
    { return mEntity.get_component<TComponent>(); }

    template<class TComponent>
    PtrView<const TComponent> FindComponent() const noexcept
    { return PtrView<const TComponent>{ mEntity.find_component<TComponent>() }; }

    int GetComponentCount() const noexcept
    { return static_cast<int>(mEntity.component_count()); }
};

} // namespace open_labora

#endif // ENTITY_HPP_
