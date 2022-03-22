#ifndef IAPPLICATIONMOCK_HPP_
#define IAPPLICATIONMOCK_HPP_

#include <gmock/gmock.h>
#include "IApplication.hpp"
#include "AppState/TestStateIds.hpp"

namespace Test
{

template<class TStateIdsVariant>
class IApplicationMock final : public OpenLabora::IApplication<TStateIdsVariant>
{
public:
    MOCK_METHOD(void, ChangeState, (TStateIdsVariant), (override));
};

} // namespace Test

#endif // IAPPLICATIONMOCK_HPP_
