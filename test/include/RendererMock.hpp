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

#ifndef RENDERERMOCK_HPP_
#define RENDERERMOCK_HPP_

#include <gmock/gmock.h>
#include <SFML/Window/Event.hpp>
#include <optional>
#include "LibTypedefs.hpp"

namespace test
{

namespace ol = open_labora;

/**
 * Mock class for graphics and GUI library wrapper.
 *
 * @tparam TWindow - Render target class of graphics library
 * @tparam TGui - GUI library class
 */
template<class TWindow, class TGui>
struct RendererMock
{
    virtual ~RendererMock() = default;

    template<class... Args>
    RendererMock(Args&&...) {};

    MOCK_METHOD(bool, IsWindowOpen, (), (const));

    MOCK_METHOD(std::optional<sf::Event>, PollEvent, (), (const));

    MOCK_METHOD(void, Clear, ());

    MOCK_METHOD(void, Draw, (ol::DrawableRangeConst));

    MOCK_METHOD(void, Display, ());

    MOCK_METHOD(bool, HandleEvent, (const sf::Event&));

    MOCK_METHOD(void, RemoveAllWidgets, ());
};

} // namespace test

#endif // Test
