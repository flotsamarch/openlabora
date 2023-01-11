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

#include <array>
#include <stdexcept>
#include <compare>
#include <cassert>
#include <Misc/IterableEnumUtilities.hpp>

namespace open_labora
{

template<class TEnumMap>
class EnumMapIterator
{
    using KeyType = typename TEnumMap::KeyType;
    using IteratorInnerType = typename TEnumMap::Container::iterator;
    using Reference =
        typename std::iterator_traits<IteratorInnerType>::reference;

    KeyType mKey{};
    IteratorInnerType mIt{};

public:
    constexpr EnumMapIterator() = default;
    constexpr EnumMapIterator(KeyType key, IteratorInnerType it);

    using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<const KeyType, Reference>;
    using reference = std::pair<const KeyType, Reference>;

private:
    template<class TReference>
    struct PointerProxy
    {
        TReference r;
        constexpr TReference* operator->() noexcept { return &r; }
    };

public:
    using pointer = PointerProxy<reference>;

    constexpr pointer operator->() const noexcept
    { return pointer{{ mKey, *mIt }}; }

    constexpr reference operator*() const noexcept
    { return { mKey, *mIt }; }

    constexpr EnumMapIterator& operator++() noexcept;

    constexpr EnumMapIterator& operator--() noexcept;

    constexpr EnumMapIterator operator--(int) noexcept;

    constexpr EnumMapIterator operator++(int) noexcept;

    constexpr auto operator<=>(const EnumMapIterator&) const = default;
};

template<class TEnumMap>
class EnumMapConstIterator
{
    using KeyType = typename TEnumMap::KeyType;
    using IteratorInnerType = typename TEnumMap::Container::const_iterator;
    using ValueType = typename IteratorInnerType::value_type;
    using Reference =
        const typename std::iterator_traits<IteratorInnerType>::reference;

    KeyType mKey{};
    IteratorInnerType mIt{};

public:
    constexpr EnumMapConstIterator() = default;
    constexpr EnumMapConstIterator(KeyType key, IteratorInnerType it);

    using iterator_concept = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = std::pair<const KeyType, Reference>;
    using reference = std::pair<const KeyType, Reference>;

private:
    template<class Reference>
    struct PointerProxy
    {
        Reference reference;
        constexpr Reference* operator->() const noexcept { return &reference; }
    };

public:
    using pointer = PointerProxy<const reference>;

    constexpr pointer operator->() const noexcept
    { return pointer{{ mKey, *mIt }}; }

    constexpr reference operator*() const noexcept
    { return { mKey, *mIt }; }

    constexpr EnumMapConstIterator& operator++() noexcept;

    constexpr EnumMapConstIterator& operator--() noexcept;

    constexpr EnumMapConstIterator operator--(int) noexcept;

    constexpr EnumMapConstIterator operator++(int) noexcept;

    constexpr auto operator<=>(const EnumMapConstIterator&) const = default;
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
template<IterableEnum TEnumKey, class TValue>
class EnumMap final
{

    static constexpr auto BeginKey = TEnumKey::Begin;
    static constexpr auto EndKey = TEnumKey::End;
    using ThisType = EnumMap<TEnumKey, TValue>;

public:
    using KeyType = TEnumKey;
    using ValueType = TValue;

    static constexpr int kItemCount =
        static_cast<int>(EndKey) - static_cast<int>(BeginKey);

    using Container = std::array<ValueType, kItemCount>;

private:
    using InitItem = std::pair<KeyType, ValueType>;

    Container mItems{};

public:
    using iterator = EnumMapIterator<ThisType>;
    using const_iterator = EnumMapConstIterator<ThisType>;

    constexpr const TValue& Get(TEnumKey key) const;

    TValue& Get(TEnumKey key);

    const TValue& At(TEnumKey key) const;

    TValue& At(TEnumKey key);

    constexpr EnumMap() = default;

    constexpr EnumMap(const std::initializer_list<InitItem>& init_list);

    constexpr int GetSize() const noexcept { return kItemCount; }

    constexpr TValue& operator[](TEnumKey key) { return Get(key); }

    constexpr const TValue& operator[](TEnumKey key) const
    { return Get(key); }

    constexpr iterator begin() noexcept
    { return iterator{ BeginKey, mItems.begin() }; }

    constexpr iterator end() noexcept
    { return iterator{ EndKey, mItems.end() }; }

    constexpr const_iterator cbegin() const noexcept
    { return const_iterator{ BeginKey, mItems.cbegin() }; }

    constexpr const_iterator cend() const noexcept
    { return const_iterator{ EndKey, mItems.cend() }; }

    constexpr const_iterator begin() const noexcept
    { return cbegin(); }

    constexpr const_iterator end() const noexcept
    { return cend(); }

    constexpr iterator Begin() noexcept
    { return begin(); }

    constexpr iterator End() noexcept
    { return end(); }

    constexpr const_iterator Begin() const noexcept
    { return cbegin(); }

    constexpr const_iterator End() const noexcept
    { return cend(); }

    constexpr const_iterator CBegin() const noexcept
    { return cbegin(); }

    constexpr const_iterator CEnd() const noexcept
    { return cend(); }

};

template<class TEnumMap>
constexpr EnumMapIterator<TEnumMap>::EnumMapIterator(KeyType key,
                                                     IteratorInnerType it)
    : mKey{ key }, mIt{ it }
{
    assert(key >= KeyType::Begin);
    assert(key <= KeyType::End);
};

template<class TEnumMap>
constexpr EnumMapIterator<TEnumMap>&
EnumMapIterator<TEnumMap>::operator++() noexcept
{
    assert(mKey < KeyType::End);
    ++mIt;
    ++mKey;
    return *this;
}

template<class TEnumMap>
constexpr EnumMapIterator<TEnumMap>&
EnumMapIterator<TEnumMap>::operator--() noexcept
{
    assert(mKey > KeyType::Begin);
    --mIt;
    --mKey;
    return *this;
}

template<class TEnumMap>
constexpr EnumMapIterator<TEnumMap>
EnumMapIterator<TEnumMap>::operator++(int) noexcept
{
    assert(mKey < KeyType::End);
    auto temp = *this;
    operator++();
    return temp;
}

template<class TEnumMap>
constexpr EnumMapIterator<TEnumMap>
EnumMapIterator<TEnumMap>::operator--(int) noexcept
{
    assert(mKey > KeyType::Begin);
    auto temp = *this;
    operator--();
    return temp;
}

template<class TEnumMap>
constexpr EnumMapConstIterator<TEnumMap>
::EnumMapConstIterator(KeyType key, IteratorInnerType it)
    : mKey{ key }, mIt{ it }
{
    assert(key >= KeyType::Begin);
    assert(key <= KeyType::End);
};

template<class TEnumMap>
constexpr EnumMapConstIterator<TEnumMap>&
EnumMapConstIterator<TEnumMap>::operator++() noexcept
{
    assert(mKey < KeyType::End);
    ++mIt;
    ++mKey;
    return *this;
}

template<class TEnumMap>
constexpr EnumMapConstIterator<TEnumMap>&
EnumMapConstIterator<TEnumMap>::operator--() noexcept
{
    assert(mKey > KeyType::Begin);
    --mIt;
    --mKey;
    return *this;
}

template<class TEnumMap>
constexpr EnumMapConstIterator<TEnumMap>
EnumMapConstIterator<TEnumMap>::operator++(int) noexcept
{
    assert(mKey < KeyType::End);
    auto temp = *this;
    operator++();
    return temp;
}

template<class TEnumMap>
constexpr EnumMapConstIterator<TEnumMap>
EnumMapConstIterator<TEnumMap>::operator--(int) noexcept
{
    assert(mKey > KeyType::Begin);
    auto temp = *this;
    operator--();
    return temp;
}

template<IterableEnum TEnumKey, class TValue>
constexpr EnumMap<TEnumKey, TValue>
::EnumMap(const std::initializer_list<InitItem>& init_list)
{
    assert(init_list.size() == kItemCount);

    #ifndef NDEBUG
    std::array<int, kItemCount> indices_count{};
    #endif

    for (auto&& [key, value] : init_list) {
        const auto index = static_cast<size_t>(key);
        assert(key >= TEnumKey::Begin);
        assert(key < TEnumKey::End);

        mItems[index] = std::move(value);
        #ifndef NDEBUG
        indices_count[index] += 1;
        #endif
    }

    #ifndef NDEBUG
    for (auto count : indices_count) {
        assert(count == 1 &&
               "Each key in map init list must appear exactly once");
    }
    #endif
}

template<IterableEnum TEnumKey, class TValue>
constexpr const TValue& EnumMap<TEnumKey, TValue>::Get(TEnumKey key) const
{
    assert(key >= TEnumKey::Begin);
    assert(key < TEnumKey::End);
    return mItems[static_cast<size_t>(key)];
}

template<IterableEnum TEnumKey, class TValue>
TValue& EnumMap<TEnumKey, TValue>::Get(TEnumKey key)
{
    assert(key >= TEnumKey::Begin);
    assert(key < TEnumKey::End);
    return mItems[static_cast<size_t>(key)];
}

template<IterableEnum TEnumKey, class TValue>
const TValue& EnumMap<TEnumKey, TValue>::At(TEnumKey key) const
{
    if (key < TEnumKey::Begin || key >= TEnumKey::End) {
        throw std::out_of_range("EnumMap: Key value outside of key range");
    }

    return mItems[static_cast<size_t>(key)];
}

template<IterableEnum TEnumKey, class TValue>
TValue& EnumMap<TEnumKey, TValue>::At(TEnumKey key)
{
    if (key < TEnumKey::Begin || key >= TEnumKey::End) {
        throw std::out_of_range("EnumMap: Key value outside of key range");
    }

    return mItems[static_cast<size_t>(key)];
}

} // namespace open_labora

#endif // ENUMMAP_HPP_
