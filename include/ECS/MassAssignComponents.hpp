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

#ifndef MASSASSIGNCOMPONENTS_HPP_
#define MASSASSIGNCOMPONENTS_HPP_

#include "Entity.hpp"

namespace open_labora
{

class MassAssignComponents final {
    Entity& entity_;

public:
    MassAssignComponents(Entity& entity) noexcept
        : entity_(entity) {}

    template <typename TComponent, typename... Args>
    MassAssignComponents& Assign(Args&&... args) {
        entity_.AssignComponent<TComponent>(std::forward<Args>(args)...);
        return *this;
    }
};

} // namespace open_labora

#endif // MASSASSIGNCOMPONENTS_HPP_
