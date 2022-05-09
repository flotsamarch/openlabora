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
#include "Misc/UID.hpp"

namespace OpenLabora
{

template<class... TComponents>
class ComponentContainer final
{
    uid::Uid mId;

public:
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

} // namespace OpenLabora

#endif // COMPONENTCONTAINER_HPP_
