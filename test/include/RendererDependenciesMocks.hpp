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
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/String.hpp>

namespace test
{

// Mock class for render target of graphics library.
struct WindowMock
{
    MOCK_METHOD(void, create, (sf::VideoMode, const std::string&, uint32_t), ());
    MOCK_METHOD(void, setFramerateLimit, (uint32_t), ());
    MOCK_METHOD(void, setVerticalSyncEnabled, (bool), ());
    MOCK_METHOD(void, resetGLStates, (), ());
    MOCK_METHOD(void, display, (), ());
    MOCK_METHOD(void, close, (), ());
    MOCK_METHOD(bool, isOpen, (), (const));
    MOCK_METHOD(void, clear, (), ());
    MOCK_METHOD(void, draw, (const sf::Drawable&), ());
    MOCK_METHOD(sf::Vector2u, getSize, (), (const));
    MOCK_METHOD(bool, pollEvent, (sf::Event&), ());
};


// Mock class for GUI library.
// @tparam TWindow - Render target class of graphics library
template<class TWindow>
struct GuiMock
{
    MOCK_METHOD(void, setTarget, (TWindow&), ());
    MOCK_METHOD(bool, handleEvent, (sf::Event), ());
    MOCK_METHOD(void, draw, (), ());
    MOCK_METHOD(void, add, (tgui::Widget::Ptr, const tgui::String&), ());
    MOCK_METHOD(void, removeAllWidgets, (), ());
};

} // namespace test

#endif // TESTRENDERERDEPENDENCIES_HPP_
