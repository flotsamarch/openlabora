#ifndef TESTRENDERERDEPENDENCIES_HPP_
#define TESTRENDERERDEPENDENCIES_HPP_

#include <gmock/gmock.h>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Window/Event.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/String.hpp>

class WindowMock final
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

class GuiMock final
{
    MOCK_METHOD(void, setTarget, (sf::RenderTarget&), ());
    MOCK_METHOD(bool, handleEvent, (sf::Event), ());
    MOCK_METHOD(void, draw, (), ());
    MOCK_METHOD(void, add, (tgui::Widget::Ptr, const tgui::String&), ());
};

#endif // TESTRENDERERDEPENDENCIES_HPP_
