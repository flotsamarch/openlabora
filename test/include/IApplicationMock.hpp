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

#ifndef IAPPLICATIONMOCK_HPP_
#define IAPPLICATIONMOCK_HPP_

#include <gmock/gmock.h>
#include "IApplication.hpp"
#include "AppState/TestStateIds.hpp"

namespace test
{

template<class TStateIdsVariant>
class IApplicationMock final : public open_labora::IApplication<TStateIdsVariant>
{
public:
    MOCK_METHOD(void, ChangeState, (TStateIdsVariant), (override));
};

} // namespace test

#endif // IAPPLICATIONMOCK_HPP_
