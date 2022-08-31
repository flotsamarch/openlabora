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
#include "Game/Components/LotDequeComponent.hpp"

namespace test
{

namespace ol = open_labora;

TEST(LotDequeComponentTests, GetLotsCount_ZeroByDefault)
{
    auto component = ol::LotDequeComponent{ ol::lot::Type::Begin };

    ASSERT_EQ(component.GetLotsCount(), 0);
}

TEST(LotDequeComponentTests, GetLotType_NeverChangedInConstructor)
{
    bool was_changed{ false };

    for (auto type = ol::lot::Type::Begin; type < ol::lot::Type::End; ++type) {
        auto component = ol::LotDequeComponent{ type };
        if (component.GetLotType() != type) {
            was_changed = true;
        }
    }

    ASSERT_FALSE(was_changed);
}

TEST(LotDequeComponentTests, GetLotsCount_IncreasedByAddingLotsToTop)
{
    constexpr auto count{ 10u };
    bool differs_from_index{ false };
    auto component = ol::LotDequeComponent{ ol::lot::Type::Begin };

    for (auto i{ 0u }; i < count; ++i) {
        component.AddLotToTop(0);
        if (component.GetLotsCount() != i + 1) {
            differs_from_index = true;
        }
    }

    ASSERT_FALSE(differs_from_index);
}

TEST(LotDequeComponentTests, GetLotsCount_IncreasedByAddingLotsToBottom)
{
    constexpr auto count{ 10u };
    bool differs_from_index{ false };
    auto component = ol::LotDequeComponent{ ol::lot::Type::Begin };

    for (auto i{ 0u }; i < count; ++i) {
        component.AddLotToBottom(0);
        if (component.GetLotsCount() != i + 1) {
            differs_from_index = true;
        }
    }

    ASSERT_FALSE(differs_from_index);
}

TEST(LotDequeComponentTests, GetLotsCount_IncreasedByAddingLotsMixed)
{
    constexpr auto count{ 10u };
    bool differs_from_index{ false };
    auto component = ol::LotDequeComponent{ ol::lot::Type::Begin };

    for (auto i{ 0u }; i < count; ++i) {
        if (i % 2 == 0) {
            component.AddLotToBottom(0);
        } else {
            component.AddLotToTop(0);
        }
        if (component.GetLotsCount() != i + 1) {
            differs_from_index = true;
        }
    }

    ASSERT_FALSE(differs_from_index);
}

TEST(LotDequeComponentsTests, OperatorSquareBrackets)
{
    constexpr auto count{ 10u };
    bool differs_from_index{ false };
    auto component = ol::LotDequeComponent{ ol::lot::Type::Begin };

    for (auto i{ 0u }; i < count; ++i) {
        component.AddLotToBottom(i);
    }

    for (auto i{ 0u }; i < count; ++i) {
        if (component[i] != i) {
            differs_from_index = true;
        }
    }

    ASSERT_FALSE(differs_from_index);
}

TEST(LotDequeComponentsTests, RangeBasedForLoop)
{
    constexpr auto count{ 10u };
    bool differs_from_index{ false };
    auto component = ol::LotDequeComponent{ ol::lot::Type::Begin };

    for (auto i{ 0u }; i < count; ++i) {
        component.AddLotToBottom(i);
    }

    for (auto i{ 0u }; auto&& subtype : component) {
        if (subtype != i) {
            differs_from_index = true;
        }
        ++i;
    }

    ASSERT_FALSE(differs_from_index);
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
