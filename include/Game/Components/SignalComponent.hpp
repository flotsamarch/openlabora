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

#include <map>
#include <unordered_map>
#include <functional>
#include "Game/Signal.hpp"
#include "Misc/EnumMap.hpp"
#include "Misc/UID.hpp"

namespace OpenLabora
{

class SignalComponent final
{
    using Serial = uint64_t;
    using DelegateMap = std::map<Serial, std::function<void()>>; // Needs order
    using SignalMap = std::unordered_map<Signal, DelegateMap, SignalHash>;
    SignalMap mSignals;

public:
    Serial Connect(const Signal& signal, std::function<void()> delegate)
    {
        const auto id = uid::getUid(uid::Type::Serial);
        // mSignals[signal].insert(std::make_pair(id, delegate));
        mSignals[signal][id] = delegate;
        return id;
    }

    void Emit(const Signal& signal)
    {
        for (auto&& [_, delegate] : mSignals[signal]) {
            delegate();
        }
    }

    void Disconnect(const Signal& signal, Serial serial)
    { mSignals[signal].erase(serial); }

    // Warning! This might break certain behavior, prefer disconnecting by serial
    void DisconnectAll(const Signal& signal)
    { mSignals[signal].clear(); }
};

} // namespace OpenLabora


#endif // SIGNALCOMPONENT_HPP_
