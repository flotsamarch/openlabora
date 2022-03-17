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

    constexpr T* Reset(T* other = nullptr) noexcept
    { mPtr = other; }

    constexpr operator bool() const noexcept
    { return Get() != nullptr; }

    constexpr std::add_lvalue_reference<T> operator*() const
    { return *Get(); }

    constexpr T* operator->() const noexcept
    { return Get(); }

    constexpr void Swap(PtrView<T>& other) noexcept
    { std::swap(other.Get(), mPtr); }

    constexpr T* Release()
    {
        T* tmp{ nullptr };
        tmp->Swap(mPtr);
        return tmp;
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
{ return lhs.Get() >= rhs.Get(); };

template<class T, class Y>
bool operator<(const PtrView<T>& lhs, const PtrView<Y>& rhs)
{ return lhs.Get() <= rhs.Get(); };

} // namespace OpenLabora

#endif // PTRVIEW_HPP_
