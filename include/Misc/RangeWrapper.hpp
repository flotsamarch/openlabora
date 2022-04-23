#ifndef RANGEWRAPPER_HPP_
#define RANGEWRAPPER_HPP_
#include <concepts>
#include <iterator>

namespace OpenLabora
{

template<class T>
class RangeWrapper final
{
    using IterCat = typename std::iterator_traits<T>::iterator_category;
    static_assert(std::is_base_of_v<std::input_iterator_tag, IterCat>,
        "Requires template parameter to be an input iterator to be used");

    T mBegin;
    T mEnd;

public:
    RangeWrapper<T>()
        : mBegin{}, mEnd{ mBegin } {}

    RangeWrapper(T begin, T end)
        : mBegin{ begin }, mEnd{ end } {}

    T begin() { return mBegin; }
    T end() { return mEnd; }

    bool IsEmpty()
    { return mBegin == mEnd; }
};

} // namespace OpenLabora

#endif // RANGEWRAPPER_HPP_
