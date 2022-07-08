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

#ifndef VIEWMOCKS_HPP_
#define VIEWMOCKS_HPP_

#include <gmock/gmock.h>
#include <SFML/Window/Event.hpp>

namespace test
{

struct GVMock1
{
    using Ptr = std::unique_ptr<GVMock1>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GVMock2
{
    using Ptr = std::unique_ptr<GVMock2>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GVMockFinal
{
    GVMockFinal() = default;
    using Ptr = std::unique_ptr<GVMockFinal>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

} // namespace test

#endif // VIEWMOCKS_HPP_
