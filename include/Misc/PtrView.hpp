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

#ifndef PTRVIEW_HPP_
#define PTRVIEW_HPP_

#include <type_traits>

namespace OpenLabora
{

// Wrapper for raw pointer with the default value set to nullptr
template<class T>
class PtrView final
{
    T* mPtr{ nullptr };

public:
    constexpr PtrView() noexcept {};
    constexpr PtrView(std::nullptr_t) noexcept {};
    constexpr explicit PtrView(T* ptr) noexcept
        : mPtr{ ptr } {};

    constexpr T* Get() const noexcept
    { return mPtr; }

    constexpr void Reset(T* other = nullptr) noexcept
    { mPtr = other; }

    constexpr operator bool() const noexcept
    { return Get() != nullptr; }

    constexpr typename std::add_lvalue_reference<T>::type operator*() const
    { return *Get(); }

    constexpr T* operator->() const noexcept
    { return Get(); }

    constexpr void Swap(PtrView<T>& other) noexcept
    { std::swap(other.mPtr, mPtr); }

    constexpr T* Release()
    {
        PtrView<T> tmp{ nullptr };
        this->Swap(tmp);
        return tmp.mPtr;
    }
};

template<class T, class Y>
bool operator==(const PtrView<T>& lhs, const PtrView<Y>& rhs)
{ return lhs.Get() == rhs.Get(); };

template<class T, class Y>
bool operator!=(const PtrView<T>& lhs, const PtrView<Y>& rhs)
{ return !(lhs == rhs); };

template<class T>
bool operator==(std::nullptr_t, const PtrView<T>& rhs) noexcept
{ return !rhs; };

template<class T>
bool operator==(const PtrView<T>& lhs, std::nullptr_t) noexcept
{ return !lhs; };

template<class T>
bool operator!=(std::nullptr_t, const PtrView<T>& rhs) noexcept
{ return rhs; };

template<class T>
bool operator!=(const PtrView<T>& lhs, std::nullptr_t) noexcept
{ return lhs; };

template<class T, class Y>
bool operator>=(const PtrView<T>& lhs, const PtrView<Y>& rhs)
{ return lhs.Get() >= rhs.Get(); };

template<class T, class Y>
bool operator<=(const PtrView<T>& lhs, const PtrView<Y>& rhs)
{ return lhs.Get() <= rhs.Get(); };

template<class T, class Y>
bool operator>(const PtrView<T>& lhs, const PtrView<Y>& rhs)
{ return lhs.Get() > rhs.Get(); };

template<class T, class Y>
bool operator<(const PtrView<T>& lhs, const PtrView<Y>& rhs)
{ return lhs.Get() < rhs.Get(); };

} // namespace OpenLabora

#endif // PTRVIEW_HPP_
