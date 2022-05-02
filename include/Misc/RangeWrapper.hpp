#ifndef RANGEWRAPPER_HPP_
#define RANGEWRAPPER_HPP_
#include <concepts>
#include <iterator>

namespace OpenLabora
{

template<class T>
concept IterableContainer = requires(T obj)
{
    typename T::iterator;
    typename T::const_iterator;
    { obj.begin() } -> std::forward_iterator<>;
    { obj.end() } -> std::forward_iterator<>;
};

/**
 * Wrapper object for begin and end iterators of a container. Intended to be used
 * in range-based-for loop
 *
 * Invalidated in the same cases as regular iterators for given container
 */
template<std::input_iterator T>
class RangeWrapper final
{
    T mBegin;
    T mEnd;

public:
    RangeWrapper()
        : mBegin{}, mEnd{ mBegin } {}

    template<IterableContainer Y>
    RangeWrapper(Y& container)
        : mBegin{ container.begin() }, mEnd{ container.end() } {}

    RangeWrapper(T begin, T end)
        : mBegin{ begin }, mEnd{ end } {}

    T begin() const { return mBegin; }
    T end() const { return mEnd; }

    bool IsEmpty() const noexcept
    { return mBegin == mEnd; }

    auto GetSize() const
    { return std::distance(mBegin, mEnd); }
};

template<IterableContainer Y>
RangeWrapper(Y& container) -> RangeWrapper<typename Y::iterator>;

template<IterableContainer Y>
RangeWrapper(const Y& container) -> RangeWrapper<typename Y::const_iterator>;

} // namespace OpenLabora

#endif // RANGEWRAPPER_HPP_