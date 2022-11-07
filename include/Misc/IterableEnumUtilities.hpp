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

#ifndef ITERABLEENUMUTILITIES_HPP_
#define ITERABLEENUMUTILITIES_HPP_

#include <type_traits>
#include <limits>
#include <iterator>

template<class T>
concept IterableEnum = requires
{
    std::is_enum_v<T>;
    std::numeric_limits<std::underlying_type<T>>::is_integer;
    { T::Begin };
    { T::End };
    T::Begin < T::End;
};

template<IterableEnum TEnum>
constexpr TEnum& operator++(TEnum& value) noexcept
{
    using Underlying = std::underlying_type_t<TEnum>;
    value = static_cast<TEnum>(static_cast<Underlying>(value) + 1);
    return value;
}

template<IterableEnum TEnum>
constexpr TEnum operator++(TEnum& value, int) noexcept
{
    using Underlying = std::underlying_type_t<TEnum>;
    auto old_value = value;
    value = static_cast<TEnum>(static_cast<Underlying>(value) + 1);
    return old_value;
}

template<IterableEnum TEnum>
constexpr TEnum& operator--(TEnum& value) noexcept
{
    using Underlying = std::underlying_type_t<TEnum>;
    value = static_cast<TEnum>(static_cast<Underlying>(value) - 1);
    return value;
}

template<IterableEnum TEnum>
constexpr TEnum operator--(TEnum& value, int) noexcept
{
    using Underlying = std::underlying_type_t<TEnum>;
    auto old_value = value;
    value = static_cast<TEnum>(static_cast<Underlying>(value) - 1);
    return old_value;
}

template<IterableEnum TEnum>
constexpr TEnum operator+(int lhs, TEnum rhs) noexcept
{
    using Underlying = std::underlying_type_t<TEnum>;
    return static_cast<TEnum>(static_cast<Underlying>(rhs) + lhs);
}

template<IterableEnum TEnum>
constexpr TEnum operator+(TEnum lhs, int rhs) noexcept
{
    using Underlying = std::underlying_type_t<TEnum>;
    return static_cast<TEnum>(static_cast<Underlying>(lhs) + rhs);
}

template<IterableEnum TEnum>
constexpr TEnum operator-(TEnum lhs, int rhs) noexcept
{
    using Underlying = std::underlying_type_t<TEnum>;
    return static_cast<TEnum>(static_cast<Underlying>(lhs) - rhs);
}

namespace open_labora
{

template<IterableEnum TEnum>
struct EnumRange final
{
    struct EnumIterator
    {
        using iterator_concept = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = TEnum;
        using reference = const TEnum&;
        using pointer = const TEnum*;

        TEnum value;

        constexpr TEnum operator*() const noexcept { return value; }

        constexpr EnumIterator operator++() noexcept { ++value; return *this; }

        constexpr bool operator==(EnumIterator rhs) const noexcept
        { return value == rhs.value; }

        constexpr bool operator!=(EnumIterator rhs) const noexcept
        { return value != rhs.value; }

        constexpr bool operator<(EnumIterator rhs) const noexcept
        { return value < rhs.value; }

        constexpr bool operator<=(EnumIterator rhs) const noexcept
        { return value <= rhs.value; }

        constexpr bool operator>(EnumIterator rhs) const noexcept
        { return value > rhs.value; }

        constexpr bool operator>=(EnumIterator rhs) const noexcept
        { return value >= rhs.value; }
    };

    constexpr EnumIterator begin() const noexcept { return{ TEnum::Begin }; }

    constexpr EnumIterator end() const noexcept { return{ TEnum::End }; }

    constexpr EnumIterator cbegin() const noexcept { return begin(); }

    constexpr EnumIterator cend() const noexcept { return end(); }
};

} // namespace open_labora

#endif // ITERABLEENUMUTILITIES_HPP_
