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

#ifndef TUPLEUTILS_HPP_
#define TUPLEUTILS_HPP_

#include <tuple>
#include <stdexcept>
#include <functional>

namespace open_labora
{

namespace tuple_utils
{

// Create tuple which consists only of type T repeated N times
template<class T, size_t N>
constexpr auto createTuple(const T& t)
{
    if constexpr (N <= 0) {
        throw std::invalid_argument{ "Cannot create zero sized tuple." };
    } else if constexpr (N == 1) {
        return std::tuple<T>{ t };
    } else {
        return std::tuple_cat(createTuple<T, N - 1>(t), std::tuple<T>{ t });
    }
}

/**
 * Apply callable to each tuple element until predicate returns false
 *
 * @tparam TCallable - Callable to apply to each element of container
 * @tparam TPredicate - Predicate which returns value of boolean type
 * @tparam Index - Tuple element index
 * @tparam Types - Tuple element types pack
 */
template<class TCallable, class TPredicate, size_t Index = 0, typename... Types>
requires requires { std::tuple_size_v<std::tuple<Types...>> > 0; }
constexpr void applyUntilFalse(std::tuple<Types...>& t,
                               TCallable&& f,
                               [[maybe_unused]]TPredicate&& p)
{
    auto&& element = std::get<Index>(t);
    std::invoke(std::forward<TCallable>(f), element);
    if constexpr (Index < std::tuple_size_v<std::tuple<Types...>> - 1) {
        if(std::invoke(std::forward<TPredicate>(p), element)) {
            applyUntilFalse<TCallable, TPredicate, Index + 1, Types...>(t, f, p);
        }
    }
}

} // namespace tuple_utils

} // namespace open_labora

#endif // TUPLEUTILS_HPP_
