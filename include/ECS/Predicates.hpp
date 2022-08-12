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

#ifndef PREDICATES_HPP_
#define PREDICATES_HPP_

#include <ecs.hpp/ecs.hpp>

namespace open_labora
{

namespace option
{

template<class TComponent>
using Exists = ecs_hpp::exists<TComponent>;

template<class... TComponents>
using ExistsAny = ecs_hpp::exists_any<TComponents...>;

template<class... TComponents>
using ExistsAll = ecs_hpp::exists_all<TComponents...>;

template<class TOption>
ecs_hpp::option_neg<TOption> Negate()
{ return { TOption{} }; }

template<class TOption>
ecs_hpp::option_neg<TOption> Negate(TOption option)
{ return { TOption{ std::move(option) } }; }

template<class... TOptions>
ecs_hpp::option_conj<TOptions...> And()
{ return { TOptions{}... }; }

template<class... TOptions>
ecs_hpp::option_conj<TOptions...> And(TOptions... options)
{ return { TOptions{ std::move(options) }... }; }

template<class... TOptions>
ecs_hpp::option_disj<TOptions...> Or()
{ return { TOptions{}... }; }

template<class... TOptions>
ecs_hpp::option_disj<TOptions...> Or(TOptions... options)
{ return { TOptions{ options }... }; }

using Bool = ecs_hpp::option_bool;

} // namespace option

} // namespace open_labora

#endif // PREDICATES_HPP_
