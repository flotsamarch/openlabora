#ifndef APPLICATIONMOCK_HPP_
#define APPLICATIONMOCK_HPP_

#include <gmock/gmock.h>
#include "../../include/IApplication.hpp"

namespace Test
{

class ApplicationMock final : public IApplication
{
public:
    MOCK_METHOD(IRenderer*, GetRenderer, (), (const, noexcept, override));
    MOCK_METHOD(
        std::shared_ptr<State>, GetState, (), (const, noexcept, override));
    MOCK_METHOD(int, run, (), (override));
};

} // namespace Test

#endif // APPLICATIONMOCK_HPP_
