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

inline Uid getUid()
{
    static Uid id{ 0u };

    if (id == std::numeric_limits<Uid>::max()) {
        throw std::overflow_error("Unable to generate UID: type overflow");
    }
    return id++;
}

} // namespace uid

} // namespace OpenLabora

#endif // UID_HPP_
