#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game/Plot.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace Test
{

using OpenLabora::plot::Plot;
using OpenLabora::plot::Type;
using OpenLabora::plot::kTextureIdMap;
using testing::Return;
using testing::ReturnRef;
using testing::StrEq;
using testing::_;
using RMM = IResourceManagerMock;

TEST(PlotTests, Create_TextureNotRegistered)
{
    auto&& res_manager = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = kTextureIdMap.Get(Type::Coastal).first;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*res_manager, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{}));

    EXPECT_CALL(*res_manager, GetTextureOrDefault)
        .WillRepeatedly(ReturnRef(texture));

    EXPECT_CALL(*res_manager, RegisterTexture(StrEq(id), _))
        .WillOnce(ReturnRef(texture));

    auto plot = OpenLabora::plot::create(Type::Coastal, sf::Vector2f{},
                                         res_manager);
}

TEST(PlotTests, Create_TextureIsRegistered)
{
    auto&& res_manager = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = kTextureIdMap.Get(Type::Coastal).first;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*res_manager, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{ texture }));

    EXPECT_CALL(*res_manager, GetTextureOrDefault)
        .Times(0);

    EXPECT_CALL(*res_manager, RegisterTexture)
        .Times(0);

    auto plot = OpenLabora::plot::create(Type::Coastal, sf::Vector2f{},
                                         res_manager);
}

TEST(PlotTests, CreateCentralInitial_TextureNotRegistered)
{
    auto&& res_manager = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = OpenLabora::plot::kCentralInitAltTextureName;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*res_manager, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{}));

    EXPECT_CALL(*res_manager, GetTextureOrDefault)
        .WillRepeatedly(ReturnRef(texture));

    EXPECT_CALL(*res_manager, RegisterTexture(StrEq(id), _))
        .WillOnce(ReturnRef(texture));

    auto plot = OpenLabora::plot::createCentralInitial(sf::Vector2f{},
                                                       res_manager,
                                                       true);
}

TEST(PlotTests, CreateCentralInitial_TextureIsRegistered)
{
    auto&& res_manager = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = OpenLabora::plot::kCentralInitAltTextureName;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*res_manager, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{ texture }));

    EXPECT_CALL(*res_manager, GetTextureOrDefault)
        .Times(0);

    EXPECT_CALL(*res_manager, RegisterTexture)
        .Times(0);

    auto plot = OpenLabora::plot::createCentralInitial(sf::Vector2f{},
                                                       res_manager,
                                                       true);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
