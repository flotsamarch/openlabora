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

#ifndef COMPONENTCONTAINER_HPP_
#define COMPONENTCONTAINER_HPP_

#include <tuple>
#include <memory>
#include "Misc/UID.hpp"

namespace open_labora
{

template<class... TComponents>
class ComponentContainer final
{
    uid::Uid mId;

public:
    using Ptr = std::shared_ptr<ComponentContainer<TComponents...>>;
    using PtrConst = std::shared_ptr<const ComponentContainer<TComponents...>>;
    using WeakPtr = std::weak_ptr<ComponentContainer<TComponents...>>;
    using WeakPtrConst = std::weak_ptr<const ComponentContainer<TComponents...>>;

    std::tuple<TComponents...> components;

    ComponentContainer(TComponents&&... args)
        : components{ std::forward<TComponents>(args)... }, mId{ uid::getUid() }
    {};

    const uid::Uid GetId() const noexcept { return mId; }
};

namespace ecs
{

template<class T, class... TComponents>
T& getComponent(ComponentContainer<TComponents...>& container) noexcept
{
    return std::get<T>(container.components);
};

template<class T, class... TComponents>
const T&
getComponent(const ComponentContainer<TComponents...>& container) noexcept
{
    return std::get<T>(container.components);
};

} // namespace ecs

} // namespace open_labora

#endif // COMPONENTCONTAINER_HPP_
