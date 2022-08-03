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

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "GameState/FinalFwd.hpp"
#include "GameState/Final.hpp"
#include "TestApplication.hpp"

namespace test
{

namespace ol = open_labora;

TEST(FinalStateTests, GetFlagIsFinal_True)
{
    auto app = TestApplication{};
    auto state = ol::Final{ ol::ApplicationContext::Ptr{ &app } };

    ASSERT_TRUE(ol::stateGetFlagIsFinal(state));
}

TEST(FinalStateTests, GetDrawableObjects_HasNone)
{
    auto app = TestApplication{};
    auto state = ol::Final{ ol::ApplicationContext::Ptr{ &app } };

    ASSERT_TRUE(ol::stateGetDrawableObjects(state).IsEmpty());
}

TEST(FinalStateTests, ChangeState)
{
    auto app = TestApplication{};

    ol::state::changeState(ol::state::Final{},
                           ol::ApplicationContext::Ptr{ &app });

    ASSERT_TRUE(stateGetFlagIsFinal(app.GetState()));
}

// stateUpdate and stateHandleInput have no body and require no testing

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
