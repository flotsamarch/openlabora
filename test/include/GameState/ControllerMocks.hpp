#ifndef TESTCONTROLLERS_HPP_
#define TESTCONTROLLERS_HPP_

#include <gmock/gmock.h>
#include <SFML/Window/Event.hpp>

namespace Test
{

struct GCMock1 final
{
    using Ptr = std::shared_ptr<GCMock1>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GCMock2 final
{
    using Ptr = std::shared_ptr<GCMock2>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GCMockFinal final
{
    using Ptr = std::shared_ptr<GCMockFinal>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

} // namespace Test

#endif // TESTCONTROLLERS_HPP_
