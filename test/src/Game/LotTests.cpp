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
#include "Game/Lot.hpp"
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"

namespace test
{

namespace ol = open_labora;
using Type = ol::lot::Type;

using testing::Return;
using testing::ReturnRef;

using LotSpriteTests = ResourceManagerDefaultActionTestBase;

static constexpr auto begin_value = static_cast<int>(Type::Begin);
static constexpr auto end_value = static_cast<int>(Type::End);
static constexpr auto range = end_value - begin_value;

TEST(LotOperatorsTests, OperatorPreincrement_Once)
{
    auto type = Type::Begin;

    ++type;

    EXPECT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::Central);
}

TEST(LotOperatorsTests, OperatorPreincrement_Loop)
{
    auto type = Type::Begin;
    for (auto i = 0; i < range; ++i) {
        ++type;
    }

    EXPECT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::End);
}

TEST(LotOperatorsTests, OperatorPlusLeft_PlusOne)
{
    auto type = Type::Begin;

    type = type + 1;

    EXPECT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::Central);
}

TEST(LotOperatorsTests, OperatorPlusLeft_PlusRange)
{
    auto type = Type::Begin;

    type = type + range;

    EXPECT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::End);
}

TEST(LotOperatorsTests, OperatorPlusRight_PlusOne)
{
    auto type = Type::Begin;

    type = 1 + type;

    EXPECT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::Central);
}

TEST(LotOperatorsTests, OperatorPlusRight_PlusRange)
{
    auto type = Type::Begin;

    type = range + type;

    EXPECT_NE(type, Type::Begin);
    ASSERT_EQ(type, Type::End);
}

TEST(LotTests, getTileCount_AlwaysGreaterThanZero)
{
    bool eq_zero{ false };

    for (auto type = Type::Begin; type < Type::End; ++type) {
        if (ol::lot::getTileCount(type) == 0) {
            eq_zero = true;
        }
    }

    ASSERT_FALSE(eq_zero);
}

TEST(LotTests, getMaximumCount_AlwaysGreaterThanZero)
{
    bool eq_zero{ false };

    for (auto type = Type::Begin; type < Type::End; ++type) {
        if (ol::lot::getTileCount(type) == 0) {
            eq_zero = true;
        }
    }

    ASSERT_FALSE(eq_zero);
}

TEST(LotTests, SubtypeId_Constructor)
{
    bool ne_init{ false };

    for(auto i = 0u; i < 10u; ++i) {
        auto subtype = ol::lot::SubtypeId{ i };
        if (static_cast<size_t>(subtype) != i) {
            ne_init = true;
        }
    }

    ASSERT_FALSE(ne_init);
}

TEST(LotTests, getLotSubtypes_AlwaysNotEmpty)
{
    bool was_empty{ false };

    for (auto type = Type::Begin; type < Type::End; ++type) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        for (auto subtype : subtypes) {
            if (subtype.empty()) {
                was_empty = true;
            }
        }
    }

    ASSERT_FALSE(was_empty);
}

TEST(LotTests, getLotSubtypeTextureNames_AlwaysNotEmpty)
{
    bool was_empty{ false };

    for (auto type = Type::Begin; type < Type::End; ++type) {
        auto texture_names = ol::lot::getLotSubtypeTextureNames(type);
        if (texture_names.empty()) {
            was_empty = true;
        }
    }

    ASSERT_FALSE(was_empty);
}

TEST(LotTests, getLotSubtypeTextureNames_AlwaysNotEmptyString)
{
    bool was_empty{ false };

    for (auto type = Type::Begin; type < Type::End; ++type) {
        auto texture_names = ol::lot::getLotSubtypeTextureNames(type);
        for (auto name : texture_names) {
            if (name == "") {
                was_empty = true;
            }
        }
    }

    ASSERT_FALSE(was_empty);
}

TEST(LotTests, getOffsetX_FirstOffsetEqualsToZero)
{
    constexpr auto type = Type::Begin;

    ASSERT_FLOAT_EQ(ol::lot::getOffsetX(type), 0.f);
}

TEST(LotTests, getOffsetX_OtherOffsetsLargerThanZero)
{
    bool eq_zero{ false };

    for (auto type = Type::Begin + 1; type < Type::End; ++type) {
        if (!std::islessgreater(ol::lot::getOffsetX(type), 0.f)) {
            eq_zero = true;
        }
    }

    ASSERT_FALSE(eq_zero);
}

TEST_F(LotSpriteTests, getSprite_CreatesAndStoresTexture)
{
    auto expected_call_count{ 0u };

    for (auto type = Type::Begin; type < Type::End; ++type) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        expected_call_count += subtypes.size();
    }

    EXPECT_CALL(*mResourceMgr, GetTexture)
        .Times(expected_call_count)
        .WillRepeatedly(Return(ResourceManagerMock::OptionalTextureRef{}));

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .Times(expected_call_count)
        .WillRepeatedly(ReturnRef(mTexture));

    for (auto type = Type::Begin; type < Type::End; ++type) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        for (auto subtype{ 0u }; [[maybe_unused]]auto _ : subtypes) {
            ol::lot::getSprite(type, subtype, mResourceMgr);
        }
    }
}

TEST_F(LotSpriteTests, getSprite_ReusesStoredTexture)
{
    auto expected_call_count{ 0u };

    for (auto type = Type::Begin; type < Type::End; ++type) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        expected_call_count += subtypes.size();
    }

    EXPECT_CALL(*mResourceMgr, GetTexture)
        .Times(expected_call_count)
        .WillRepeatedly(Return(mTexture));

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .Times(0);

    for (auto type = Type::Begin; type < Type::End; ++type) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        for (auto subtype{ 0u }; [[maybe_unused]]auto _ : subtypes) {
            ol::lot::getSprite(type, subtype, mResourceMgr);
        }
    }
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
