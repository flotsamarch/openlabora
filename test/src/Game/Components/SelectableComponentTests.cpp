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
#include "Game/Components/SelectableComponent.hpp"

namespace test
{

class SelectableComponentsTests : public testing::Test
{
protected:
    open_labora::SelectableComponent mComponent{};
};

TEST_F(SelectableComponentsTests, DefaultDeselected)
{
    ASSERT_FALSE(mComponent.IsSelected());
}

TEST_F(SelectableComponentsTests, DefaultNotEntered)
{
    ASSERT_FALSE(mComponent.HasBeenEntered());
}

TEST_F(SelectableComponentsTests, Select)
{
    mComponent.Select();

    ASSERT_TRUE(mComponent.IsSelected());
}

TEST_F(SelectableComponentsTests, Deselect)
{
    mComponent.Select();
    mComponent.Deselect();

    ASSERT_FALSE(mComponent.IsSelected());
}

TEST_F(SelectableComponentsTests, Enter)
{
    mComponent.Enter();

    ASSERT_TRUE(mComponent.HasBeenEntered());
}

TEST_F(SelectableComponentsTests, Leave)
{
    mComponent.Enter();
    mComponent.Leave();

    ASSERT_FALSE(mComponent.HasBeenEntered());
}

} // namespace test

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
