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

inline std::ostream& operator<<(std::ostream& ostream,
                                const open_labora::lot::Type& type)
{
    return (ostream << "LotType = " << static_cast<int>(type));
}

template<>
inline testing::Message&
testing::Message
::operator<<<open_labora::lot::Type>(const open_labora::lot::Type& type)
{
    return (*this << "LotType = " << static_cast<int>(type));
}

namespace test
{

namespace ol = open_labora;
using Type = ol::lot::Type;

using testing::Return;
using testing::ReturnRef;

using LotSpriteTests = ResourceManagerDefaultActionTestBase;

TEST(LotTests, getTileCount_AlwaysGreaterThanZero)
{
    for (auto type : ol::EnumRange<Type>{}) {
        ASSERT_GT(ol::lot::getTileCount(type), 0) << type;
    }
}

TEST(LotTests, getMaximumCount_AlwaysGreaterThanZero)
{
    for (auto type : ol::EnumRange<Type>{}) {
        ASSERT_GT(ol::lot::getMaximumCount(type), 0) << type;
    }
}

TEST(LotTests, SubtypeId_Constructor)
{
    for (auto i = 0; i < 10; ++i) {
        auto subtype = ol::lot::SubtypeId{ i };
        ASSERT_EQ(static_cast<int>(subtype), i);
    }
}

TEST(LotTests, getLotSubtypes_AlwaysNotEmpty)
{
    for (auto type : ol::EnumRange<Type>{}) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        for (auto subtype : subtypes) {
            ASSERT_FALSE(subtype.empty()) << "Empty lot subtype defined for "
                                          << type;
        }
    }
}

TEST(LotTests, getLotSubtypeTextureNames_AlwaysNotEmpty)
{
    for (auto type : ol::EnumRange<Type>{}) {
        auto texture_names = ol::lot::getLotSubtypeTextureNames(type);
        ASSERT_FALSE(texture_names.empty()) << "Empty texture name defined "
                                            << "for lot subtybe where "
                                            << type;
    }
}

TEST(LotTests, getLotSubtypeTextureNames_AlwaysNotEmptyString)
{
    for (auto type : ol::EnumRange<Type>{}) {
        auto texture_names = ol::lot::getLotSubtypeTextureNames(type);
        for (auto name : texture_names) {
            ASSERT_NE(name, "") << "Empty texture name defined "
                                << "for lot subtybe where "
                                << type;
        }
    }
}

TEST(LotTests, getOffsetX_FirstOffsetEqualsToZero)
{
    constexpr auto type = Type::Begin;

    ASSERT_FLOAT_EQ(ol::lot::getOffsetX(type), 0.f);
}

TEST(LotTests, getOffsetX_OtherOffsetsLargerThanZero)
{
    for (auto type = Type::Begin + 1; type < Type::End; ++type) {
        ASSERT_NE(ol::lot::getOffsetX(type), 0.f) << type;
    }
}

TEST(LotTests, GetAnchorLotType_CentralIsAnchorToCentral)
{
    constexpr auto anchor = getAnchorLotType(Type::Central);

    ASSERT_EQ(anchor, Type::Central);
}

TEST(LotTests, GetAnchorLotType_BeforeCentralNextIsAnchor)
{
    auto last = ol::lot::Type::Begin;

    for (auto type = ol::lot::Type::Begin + 1; type != Type::Central; ++type) {
        auto anchor = getAnchorLotType(last);

        ASSERT_EQ(type, anchor) << type;
        last = anchor;
    }
}

TEST(LotTests, GetAnchorLotType_AfterCentralPreviousIsAnchor)
{
    auto last = Type::Central;

    for (auto type = Type::Central + 1; type != ol::lot::Type::End; ++type) {
        auto anchor = getAnchorLotType(type);

        ASSERT_EQ(anchor, last) << type;
        last = type;
    }
}


TEST_F(LotSpriteTests, getSprite_CreatesAndStoresTexture)
{
    auto expected_call_count = 0;

    for (auto type : ol::EnumRange<Type>{}) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        expected_call_count += subtypes.size();
    }

    EXPECT_CALL(*mResourceMgr, GetTexture)
        .Times(expected_call_count)
        .WillRepeatedly(Return(ResourceManagerMock::OptionalTextureRef{}));

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .Times(expected_call_count)
        .WillRepeatedly(ReturnRef(mTexture));

    for (auto type : ol::EnumRange<Type>{}) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        for (auto subtype = 0; [[maybe_unused]]auto _ : subtypes) {
            ol::lot::getSprite(type, subtype, mResourceMgr);
        }
    }
}

TEST_F(LotSpriteTests, getSprite_ReusesStoredTexture)
{
    auto expected_call_count = 0;

    for (auto type : ol::EnumRange<Type>{}) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        expected_call_count += subtypes.size();
    }

    EXPECT_CALL(*mResourceMgr, GetTexture)
        .Times(expected_call_count)
        .WillRepeatedly(Return(mTexture));

    EXPECT_CALL(*mResourceMgr, StoreTexture)
        .Times(0);

    for (auto type : ol::EnumRange<Type>{}) {
        auto subtypes = ol::lot::getLotSubtypes(type);
        for (auto subtype = 0; [[maybe_unused]]auto _ : subtypes) {
            ol::lot::getSprite(type, subtype, mResourceMgr);
        }
    }
}

} // namespace test

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
