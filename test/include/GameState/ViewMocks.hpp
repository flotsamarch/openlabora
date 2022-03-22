#ifndef VIEWMOCKS_HPP_
#define VIEWMOCKS_HPP_

#include <gmock/gmock.h>
#include <SFML/Window/Event.hpp>

namespace Test
{

struct GVMock1 final
{
    using Ptr = std::unique_ptr<GVMock1>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GVMock2 final
{
    using Ptr = std::unique_ptr<GVMock2>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

struct GVMockFinal final
{
    using Ptr = std::unique_ptr<GVMockFinal>;
    MOCK_METHOD(void, HandleEvent, (const sf::Event&), ());
    MOCK_METHOD(void, Update, (const float), ());
};

} // namespace Test

#endif // VIEWMOCKS_HPP_
