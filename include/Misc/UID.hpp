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

#ifndef UID_HPP_
#define UID_HPP_
#include <cstdint>
#include <limits>
#include <stdexcept>
#include "EnumMap.hpp"

namespace OpenLabora
{

namespace uid
{

using Uid = uint64_t;

enum Type
{
    Begin, General = Begin, Signal, Serial, End
};

inline Uid getUid(Type type = Type::General)
{
    static EnumMap<Type, Uid> ids;

    auto&& id = ids.Get(type);
    if (id == std::numeric_limits<Uid>::max()) {
        throw std::overflow_error("Unable to generate UID: type overflow");
    }
    return id++;
}

} // namespace uid

} // namespace OpenLabora

#endif // UID_HPP_
