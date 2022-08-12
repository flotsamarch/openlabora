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

#ifndef REGISTRY_HPP_
#define REGISTRY_HPP_

#include <ecs.hpp/ecs.hpp>
#include "Entity.hpp"
#include "Feature.hpp"

namespace open_labora
{

template<class T>
concept CFeatureId = requires(T t)
{
    T{};
    std::is_empty_v<T>;
};

template<class TRegistry>
class RegistryWrapper final
{
    static constexpr auto kIsReference = std::is_reference_v<TRegistry>;
    static constexpr auto kIsNoexceptCtor = noexcept(kIsReference);
    TRegistry mRegistry;

public:
    RegistryWrapper()
        : mRegistry{} {};

    /**
     * ecs_hpp::registry copy ctor is deleted, so this is used to create a
     * wrapper for std::reference_wrapper<ecs_hpp::registry> which is needed e.g.
     * in ForEachEntity(...) callback and will be deduced
     */
    RegistryWrapper(TRegistry registry) noexcept(kIsNoexceptCtor)
        : mRegistry{ registry } {};

    Entity CreateEntity() noexcept
    { return { mRegistry.create_entity() }; }

    // TODO Entity CreateEntity(Prototype)

    void DestroyEntity(EntityId id) noexcept
    { mRegistry.destroy_entity(id); }

    void DestroyEntity(const Entity& entity) noexcept
    { mRegistry.destroy_entity(entity.GetId()); }

    bool IsEntityValid(EntityId id) const noexcept
    { return mRegistry.valid_entity(id); }

    bool IsEntityValid(const Entity& entity) const noexcept
    { return mRegistry.valid_entity(entity.GetId()); }

    size_t EntityCount() const noexcept
    { return mRegistry.entity_count(); }

    template<class TComponent, class TCallable, class... Opts>
    void ForEachComponent(TCallable&& callable, Opts&&... opts)
    {
        // Wrap to allow ecs_hpp::entity -> ol::Entity conversion
        auto wrapped = [&callable] (ecs_hpp::entity entity, TComponent& comp)
        {
            std::invoke(callable, entity, comp);
        };

        mRegistry.template
            for_each_component<TComponent>(wrapped,
                                           std::forward<Opts>(opts)...);
    }

    template<class TComponent, class TCallable, class... Opts>
    void ForEachComponent(TCallable&& callable, Opts&&... opts) const
    {
        // Wrap to allow ecs_hpp::const_entity -> ol::ConstEntity conversion
        auto wrapped = [&callable]
        (ecs_hpp::const_entity entity, const TComponent& comp)
        {
            std::invoke(callable, entity, comp);
        };

        mRegistry.template
            for_each_component<TComponent>(wrapped,
                                           std::forward<Opts>(opts)...);
    }

    template<class TCallable, class... Opts>
    void ForEachEntity(TCallable&& callable, Opts&&... opts)
    {
        // Wrap to allow ecs_hpp::entity -> ol::Entity conversion
        auto wrapped = [&callable] (ecs_hpp::entity entity)
        {
            std::invoke(callable, entity);
        };

        mRegistry.for_each_entity(wrapped, std::forward<Opts>(opts)...);
    }

    template<class TCallable, class... Opts>
    void ForEachEntity(TCallable&& callable, Opts&&... opts) const
    {
        // Wrap to allow ecs_hpp::const_entity -> ol::ConstEntity conversion
        auto wrapped = [&callable] (ecs_hpp::const_entity entity)
        {
            std::invoke(callable, entity);
        };

        mRegistry.for_each_entity(wrapped, std::forward<Opts>(opts)...);
    }

    template<class... TCompts, class TCallable, class... Opts>
    void ForJoinedComponents(TCallable&& callable, Opts&&... opts)
    {
        // Wrap to allow ecs_hpp::entity -> ol::Entity conversion
        auto wrapped = [&callable, this]
        (ecs_hpp::entity entity, TCompts&... compts)
        {
            std::invoke(callable, entity, compts...);
        };

        mRegistry.template
            for_joined_components<TCompts...>(wrapped,
                                              std::forward<Opts>(opts)...);
    }

    template<class... TCompts, class TCallable, class... Opts>
    void ForJoinedComponents(TCallable&& callable, Opts&&... opts) const
    {
        // Wrap to allow ecs_hpp::const_entity -> ol::ConstEntity conversion
        auto wrapped = [&callable]
        (ecs_hpp::const_entity entity, const TCompts&... compts)
        {
            std::invoke(callable, entity, compts...);
        };

        mRegistry.template
            for_joined_components<TCompts...>(wrapped,
                                              std::forward<Opts>(opts)...);
    }

    template<CFeatureId TFeature, class... Args>
    Feature AssignFeature(Args&&... args)
    {
        return mRegistry.template
            assign_feature<TFeature>(std::forward<Args>(args)...);
    }

    template<CFeatureId TFeature, class... Args>
    Feature GetOrCreateFeature(Args&&... args)
    {
        return mRegistry.template
            ensure_feature<TFeature>(std::forward<Args>(args)...);
    }

    template<CFeatureId TFeature>
    Feature GetFeature()
    { return { mRegistry.template get_feature<TFeature>() }; }

    template<CFeatureId TFeature>
    ConstFeature GetFeature() const
    { return { mRegistry.template get_feature<TFeature>() }; }

    template<class TEvent>
    RegistryWrapper& HandleEvent(const TEvent& event)
    { mRegistry.process_event(event); return *this; }

    operator RegistryWrapper<ecs_hpp::registry&>()
    {
        return{ mRegistry };
    }
};

using Registry = RegistryWrapper<ecs_hpp::registry>;
using RegistryRef = RegistryWrapper<ecs_hpp::registry&>;

} // namespace open_labora

#endif // REGISTRY_HPP_
