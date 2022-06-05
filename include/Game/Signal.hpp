#ifndef SIGNAL_HPP_
#define SIGNAL_HPP_

#include <compare>
#include "Misc/UID.hpp"

namespace OpenLabora
{

class Signal
{
    uid::Uid mId;
public:
    Signal() : mId{ uid::getUid(uid::Type::Signal) } {}

    uid::Uid GetId() const noexcept { return mId; }
    auto operator<=>(const Signal&) const noexcept = default;
};

struct SignalHash
{
    std::size_t operator()(const OpenLabora::Signal& signal) const noexcept
    {
        return static_cast<std::size_t>(signal.GetId());
    }
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

} // namespace OpenLabora

#endif // SIGNAL_HPP_
