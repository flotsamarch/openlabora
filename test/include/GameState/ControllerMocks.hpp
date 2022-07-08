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

#ifndef TESTCONTROLLERS_HPP_
#define TESTCONTROLLERS_HPP_

#include <gmock/gmock.h>
#include <SFML/Window/Event.hpp>

namespace test
{

struct GCMock1
{
    using Ptr = std::shared_ptr<GCMock1>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GCMock2
{
    using Ptr = std::shared_ptr<GCMock2>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GCMockFinal
{
    GCMockFinal() = default;
    using Ptr = std::shared_ptr<GCMockFinal>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

} // namespace test

#endif // TESTCONTROLLERS_HPP_
