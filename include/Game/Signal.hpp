#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include <compare>
#include "Misc/UID.hpp"

namespace open_labora
{

class Signal
{
    uid::Uid mId;
public:
    Signal() : mId{ uid::getUid(uid::Type::Signal) } {}

    uid::Uid GetId() const noexcept { return mId; }
    auto operator<=>(const Signal&) const noexcept = default;
};

namespace signals
{

inline const Signal kOnMouseEnter{};
inline const Signal kOnMouseLeave{};
inline const Signal kOnLeftPress{};
inline const Signal kOnLeftRelease{};
inline const Signal kOnRightPress{};
inline const Signal kOnRightRelease{};
inline const Signal kOnMiddlePress{};
inline const Signal kOnMiddleRelease{};

} // namespace signals

} // namespace open_labora

template<>
struct std::hash<open_labora::Signal>
{
    std::size_t operator()(const open_labora::Signal& signal) const noexcept
    { return std::hash<decltype(signal.GetId())>{}(signal.GetId()); }
};


#endif // SIGNAL_HPP_
