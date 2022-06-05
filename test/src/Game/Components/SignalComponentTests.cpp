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

#include <gtest/gtest.h>
#include "Game/Components/SignalComponent.hpp"

namespace Test
{

using OpenLabora::SignalComponent;
using OpenLabora::signals::kOnLeftPress;

class SignalComponentTests : public ::testing::Test
{
protected:
    SignalComponent mComponent{};
};

TEST_F(SignalComponentTests, Connect)
{
    auto delegate = [] {};
    auto serial_1 = mComponent.Connect(kOnLeftPress, delegate);
    auto serial_2 = mComponent.Connect(kOnLeftPress, delegate);
    auto serial_3 = mComponent.Connect(kOnLeftPress, delegate);

    EXPECT_EQ(serial_1, 0u);
    EXPECT_EQ(serial_2, 1u);
    ASSERT_EQ(serial_3, 2u);
}

TEST_F(SignalComponentTests, Emit)
{
    bool changed = false;
    auto delegate = [&changed] { changed = true; };

    mComponent.Connect(kOnLeftPress, delegate);
    mComponent.Emit(kOnLeftPress);

    ASSERT_EQ(changed, true);
}

TEST_F(SignalComponentTests, Disconnect)
{
    bool changed = false;
    auto delegate = [&changed] { changed = true; };

    auto serial = mComponent.Connect(kOnLeftPress, delegate);
    mComponent.Disconnect(kOnLeftPress, serial);
    mComponent.Emit(kOnLeftPress);

    ASSERT_EQ(changed, false);
}

TEST_F(SignalComponentTests, DisconnectAll)
{
    bool changed = false;
    auto delegate = [&changed] { changed = true; };

    mComponent.Connect(kOnLeftPress, delegate);
    mComponent.DisconnectAll(kOnLeftPress);
    mComponent.Emit(kOnLeftPress);

    ASSERT_EQ(changed, false);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
