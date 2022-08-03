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

#ifndef GAMEWINDOWMOCK_HPP_
#define GAMEWINDOWMOCK_HPP_

#include <gmock/gmock.h>
#include "IGameWindow.hpp"

namespace test
{

namespace ol = open_labora;

struct GameWindowMock : ol::IGameWindow
{
    MOCK_METHOD(void, SetView, (const ol::View&), (override));

    MOCK_METHOD(const ol::View&, GetView, (), (const, override));

    MOCK_METHOD(ol::Vector2u, GetWindowSize, (), (const, override));

    MOCK_METHOD(ol::Vector2f, MapScreenToWorldCoords,
                (const ol::Vector2i&), (const, override));

    MOCK_METHOD(ol::Vector2i, MapWorldToScreenCoords,
                (const ol::Vector2f& coord), (const, override));

    MOCK_METHOD(void, AddWidget, (ol::Widget::Ptr, const ol::GuiString&),
                (const, override));

    MOCK_METHOD(void, AddWidget, (ol::Widget::Ptr), (const, override));

    MOCK_METHOD(void, RemoveAllWidgets, (), (override));
};


} // namespace test

#endif // GAMEWINDOWMOCK_HPP_
