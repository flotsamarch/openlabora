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

#ifndef MODELMOCK_HPP_
#define MODELMOCK_HPP_

#include <gmock/gmock.h>
#include "Misc/PtrView.hpp"
#include "LibTypedefs.hpp"
#include "ECS/Registry.hpp"

namespace test
{

namespace ol = open_labora;

struct ModelMock
{
    virtual ~ModelMock() = default;

    using Ptr = ol::PtrView<ModelMock>;

    MOCK_METHOD(bool, IsPaused, (), (const, noexcept));

    MOCK_METHOD(void, SetPaused, (bool), (noexcept));

    MOCK_METHOD(ol::DrawableRangeConst, GetDrawableObjects, (),
                (const, noexcept));

    MOCK_METHOD(void, ClearDrawableObjects, (), (noexcept));

    MOCK_METHOD(void, AddDrawableObject, (const ol::Drawable&), (noexcept));

    MOCK_METHOD(void, SetWorldMousePosition, (const ol::Vector2f&));

    MOCK_METHOD(ol::Vector2f, GetWorldMousePosition, (), (const));

    MOCK_METHOD(ol::Registry&, GetRegistry, (), (noexcept));

    MOCK_METHOD(const ol::Registry&, GetRegistry, (), (const, noexcept));
};

} // namespace test

#endif // MODELMOCK_HPP_
