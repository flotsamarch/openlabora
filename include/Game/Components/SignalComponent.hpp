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

#ifndef SIGNALCOMPONENT_HPP_
#define SIGNALCOMPONENT_HPP_

#include <unordered_map>
#include <functional>
#include "Misc/EnumMap.hpp"
#include "Misc/UID.hpp"

namespace OpenLabora
{

enum class Signals
{
    Begin,
    OnMouseEnter = Begin, OnMouseLeave,
    OnLeftClick, OnLeftPressed, OnLeftReleased,
    OnRightClicked, OnRightPressed, OnRightReleased,
    End
};

class SignalComponent final
{
    using Serial = uint64_t;
    using DelegateMap = std::unordered_map<Serial, std::function<void()>>;
    EnumMap<Signals, DelegateMap> mSignals;

public:
    Serial Connect(Signals signal, std::function<void()> delegate)
    {
        auto id = uid::getUid(uid::Type::Serial);
        mSignals.Get(signal).insert(std::make_pair(id, delegate));
        return id;
    }

    void Emit(Signals signal)
    { for (auto&& [id, delegate] : mSignals.Get(signal)) { delegate(); } }

    void Disconnect(Signals signal, Serial serial)
    { mSignals.Get(signal).erase(serial); }

    // Warning! This might break certain behavior, prefer disconnecting by serial
    void DisconnectAll(Signals signal)
    { mSignals.Get(signal).clear(); }
};

} // namespace OpenLabora

#endif // SIGNALCOMPONENT_HPP_
