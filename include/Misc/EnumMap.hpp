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

#ifndef ENUMMAP_HPP_
#define ENUMMAP_HPP_

#include <type_traits>
#include <utility>
#include <array>
#include <stdexcept>
#include <compare>

namespace open_labora
{

template<class T>
concept MappableEnum = requires
{
    std::is_enum_v<T>;
    { T::Begin };
    { T::End };
    T::Begin < T::End;
};

template<class TItem, class TIterItem, bool IsConst>
class EnumMapIteratorTraitsHelper{};

template<class TItem, class TIterItem>
struct EnumMapIteratorTraitsHelper<TItem, TIterItem, false>
{
    using PtrType = TIterItem*; // Pointer type wrapped by iterator
    using InitPtrType = TItem*; // Type for iterator initialization
    using difference_type = std::ptrdiff_t;
    using reference = TIterItem&;
    using pointer = TIterItem*;
};

template<class TItem, class TIterItem>
struct EnumMapIteratorTraitsHelper<TItem, TIterItem, true>
{
    using PtrType = const TIterItem*;
    using InitPtrType = const TItem*;
    using difference_type = std::ptrdiff_t;
    using reference = const TIterItem&;
    using pointer = const TIterItem*;
};

/**
 * EnumMap - associative container for key-value pairs where keys are enumerator
 * identifiers.
 *
 * @tparam TEnumKey - Enum to use as keys. Enum must be contiguous. Enum must
 * contain members ::Begin and ::End for size calculation
 *
 * @tparam TValue - Type of mapped values
 */
template<MappableEnum TEnumKey, class TValue>
class EnumMap final
{
    using Item = std::pair<TEnumKey, TValue>; // type of items in map

    static constexpr auto Begin = TEnumKey::Begin;
    static constexpr auto End = TEnumKey::End;

    static constexpr size_t kItemCount =
        static_cast<size_t>(End) - static_cast<size_t>(Begin);

    using Container = std::array<Item, kItemCount>;

    // Type that is iterated over. Protects the key from being changed.
    using IterItem = std::pair<const TEnumKey, TValue>;

    template<bool IsConst>
    class IteratorImpl
    {
        using Traits = EnumMapIteratorTraitsHelper<Item, IterItem, IsConst>;

        // Select correct types based on constness of iterator
        using PtrType = typename Traits::PtrType;
        using InitPtrType = typename Traits::InitPtrType;
        using Iterator = IteratorImpl<IsConst>;

        PtrType mPtr;

    public:
        constexpr IteratorImpl() = default;
        constexpr IteratorImpl(InitPtrType ptr)
            : mPtr{ reinterpret_cast<PtrType>(ptr) } {};

        using iterator_concept = std::bidirectional_iterator_tag;
        using difference_type = typename Traits::difference_type;
        using value_type = std::pair<const TEnumKey, TValue>;
        using reference = typename Traits::reference;
        using pointer = typename Traits::pointer;

        constexpr pointer operator->() const noexcept { return mPtr; }

        constexpr reference operator*() const noexcept { return *mPtr; }

        constexpr Iterator& operator++() noexcept { ++mPtr; return *this; }

        constexpr Iterator& operator--() noexcept { --mPtr; return *this; }

        constexpr Iterator operator--(int) noexcept
        { auto temp = *this; operator--(); return temp; }

        constexpr Iterator operator++(int) noexcept
        { auto temp = *this; operator++(); return temp; }

        auto operator<=>(const IteratorImpl<IsConst>&) const = default;
    };

    Container mItems{};

public:
    using iterator = IteratorImpl<false>;
    using const_iterator = IteratorImpl<true>;

    constexpr const TValue& Get(TEnumKey key) const;

    TValue& Get(TEnumKey key);

    constexpr EnumMap();

    constexpr EnumMap(const std::initializer_list<Item>& list);

    constexpr size_t GetSize() const noexcept { return kItemCount; }

    constexpr TValue& operator[](TEnumKey key) noexcept { return Get(key); }

    constexpr const TValue& operator[](TEnumKey key) const noexcept
    { return Get(key); }

    constexpr iterator begin() noexcept
    { return iterator{ &mItems.front() }; }

    constexpr iterator end() noexcept
    { return iterator{ &mItems.back() + 1 }; }

    constexpr const_iterator begin() const noexcept
    { return const_iterator{ &mItems.front() }; }

    constexpr const_iterator end() const noexcept
    { return const_iterator{ &mItems.back() + 1 }; }

    constexpr const_iterator cbegin() const noexcept
    { return const_iterator{ &mItems.front() }; }

    constexpr const_iterator cend() const noexcept
    { return const_iterator{ &mItems.back() + 1 }; }

};

template<MappableEnum TEnumKey, class TValue>
constexpr const TValue& EnumMap<TEnumKey, TValue>::Get(TEnumKey key) const
{
    if (key < TEnumKey::Begin || key >= TEnumKey::End) {
        throw std::range_error("EnumMap: Enum value outside of range");
    }

    return mItems[static_cast<size_t>(key)].second;
}

template<MappableEnum TEnumKey, class TValue>
TValue& EnumMap<TEnumKey, TValue>::Get(TEnumKey key)
{
    if (key < TEnumKey::Begin || key >= TEnumKey::End) {
        throw std::range_error("EnumMap: Enum value outside of range");
    }

    return mItems[static_cast<size_t>(key)].second;
}

template<MappableEnum TEnumKey, class TValue>
constexpr EnumMap<TEnumKey, TValue>::EnumMap()
{
    for (size_t i = 0; auto&& item : mItems) {
        item.first = static_cast<TEnumKey>(i++);
    }
}

template<MappableEnum TEnumKey, class TValue>
constexpr EnumMap<TEnumKey, TValue>
::EnumMap(const std::initializer_list<Item>& list)
{
    if (list.size() != kItemCount) {
        throw std::invalid_argument("Not all enum values are used");
    }

    for (size_t i = 0; auto&& item : list) {
        const auto index = static_cast<size_t>(item.first);
        const bool is_in_range = item.first >= TEnumKey::Begin &&
                                 item.first < TEnumKey::End;

        if (!is_in_range) {
            throw std::invalid_argument("Enum value outside of range");
        }

        for (size_t j = 0; auto&& inner : list) {
            if (j == i) {
                ++j;
                continue;
            }

            if (inner.first == item.first) {
                constexpr std::string_view err_msg =
                    "Multiple values for one key are not allowed";
                throw std::invalid_argument(err_msg.data());
            }
            ++j;
        }

        mItems[index] = item;
        ++i;
    }
}

} // namespace open_labora

#endif // ENUMMAP_HPP_
