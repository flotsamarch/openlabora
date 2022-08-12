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

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <ecs.hpp/ecs.hpp>
#include <concepts>

namespace open_labora
{

template<class TDerived, class... TEvents>
class System;

template<class TDerived>
class System<TDerived> : public virtual ecs_hpp::system<>{};

template<class TDerived, class TEvent>
class System<TDerived, TEvent> : public System<TDerived>,
                                 public virtual ecs_hpp::system<TEvent>
{
    void process(ecs_hpp::registry& owner, const TEvent& event) override
    { systemHandleEvent(static_cast<TDerived&>(*this), owner, event); }
};

template<class TDerived, class TEvent, class... TEvents>
class System<TDerived, TEvent, TEvents...> : public System<TDerived, TEvent>,
                                             public System<TDerived, TEvents...>
{
};



} // namespace open_labora

#endif // SYSTEM_HPP_
