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

namespace test
{

namespace ol = open_labora;

class SignalComponentTests : public testing::Test
{
protected:
    ol::SignalComponent mComponent{};
};

TEST_F(SignalComponentTests, Connect)
{
    auto delegate = [] {};
    auto serial_1 = mComponent.Connect(ol::signals::kOnLeftPress, delegate);
    auto serial_2 = mComponent.Connect(ol::signals::kOnLeftPress, delegate);
    auto serial_3 = mComponent.Connect(ol::signals::kOnLeftPress, delegate);

    EXPECT_EQ(serial_1, 0);
    EXPECT_EQ(serial_2, 1);
    ASSERT_EQ(serial_3, 2);
}

TEST_F(SignalComponentTests, Emit)
{
    bool changed = false;
    auto delegate = [&changed] { changed = true; };

    mComponent.Connect(ol::signals::kOnLeftPress, delegate);
    mComponent.Emit(ol::signals::kOnLeftPress);

    ASSERT_EQ(changed, true);
}

TEST_F(SignalComponentTests, Disconnect)
{
    bool changed = false;
    auto delegate = [&changed] { changed = true; };

    auto serial = mComponent.Connect(ol::signals::kOnLeftPress, delegate);
    mComponent.Disconnect(ol::signals::kOnLeftPress, serial);
    mComponent.Emit(ol::signals::kOnLeftPress);

    ASSERT_EQ(changed, false);
}

TEST_F(SignalComponentTests, DisconnectAll)
{
    bool changed = false;
    auto delegate = [&changed] { changed = true; };

    mComponent.Connect(ol::signals::kOnLeftPress, delegate);
    mComponent.DisconnectAll(ol::signals::kOnLeftPress);
    mComponent.Emit(ol::signals::kOnLeftPress);

    ASSERT_EQ(changed, false);
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
