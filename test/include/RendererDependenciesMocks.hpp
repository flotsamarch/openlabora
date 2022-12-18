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

#ifndef TESTRENDERERDEPENDENCIES_HPP_
#define TESTRENDERERDEPENDENCIES_HPP_

#include <gmock/gmock.h>
#include <SFML/Window/Event.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/String.hpp>
#include "LibTypedefs.hpp"
#include "GUI/GuiTypedefs.hpp"

namespace test
{

namespace ol = open_labora;

// Mock class for render target of graphics library.
struct WindowMock
{
    virtual ~WindowMock() = default;

    MOCK_METHOD(void, create, (ol::VideoMode,
                               const std::string& window_title, int), ());

    MOCK_METHOD(void, setFramerateLimit, (int), ());

    MOCK_METHOD(void, setVerticalSyncEnabled, (bool), ());

    MOCK_METHOD(void, resetGLStates, (), ());

    MOCK_METHOD(void, display, (), ());

    MOCK_METHOD(void, close, (), ());

    MOCK_METHOD(bool, isOpen, (), (const));

    MOCK_METHOD(void, clear, (), ());

    MOCK_METHOD(void, draw, (const ol::Drawable&), ());

    MOCK_METHOD(ol::Vector2u, getSize, (), (const));

    MOCK_METHOD(bool, pollEvent, (sf::Event&), ());
};


// Mock class for GUI library.
// @tparam TWindow - Render target class of graphics library
template<class TWindow>
struct GuiMock
{
    virtual ~GuiMock() = default;

    MOCK_METHOD(void, setTarget, (TWindow&), ());

    MOCK_METHOD(bool, handleEvent, (sf::Event), ());

    MOCK_METHOD(void, draw, (), ());

    MOCK_METHOD(void, add, (ol::Widget::Ptr, const ol::GuiString& name), ());

    MOCK_METHOD(void, removeAllWidgets, (), ());
};

} // namespace test

#endif // TESTRENDERERDEPENDENCIES_HPP_
