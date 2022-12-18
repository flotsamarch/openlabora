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

#ifndef POSITIONCOMPONENT_HPP_
#define POSITIONCOMPONENT_HPP_

#include "LibTypedefs.hpp"

namespace open_labora
{

struct PositionComponent final
{
    float x = 0.f;
    float y = 0.f;

    PositionComponent() noexcept = default;

    PositionComponent(float _x, float _y) noexcept
        : x{ _x }, y{ _y }
    {
    }

    PositionComponent(const Vector2f& position) noexcept
        : x{ position.x }, y{ position.y }
    {
    }

    operator Vector2f() const
    { return { x, y }; }
};

} // namespace open_labora

#endif // POSITIONCOMPONENT_HPP_
