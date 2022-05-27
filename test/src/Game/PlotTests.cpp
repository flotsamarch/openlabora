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
#include <gmock/gmock.h>
#include "Game/Plot.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace Test
{

using OpenLabora::Plot;
using OpenLabora::plot::Type;
using OpenLabora::plot::kTextureIdMap;
using testing::Return;
using testing::ReturnRef;
using testing::StrEq;
using testing::_;
using RMM = IResourceManagerMock;

TEST(PlotTests, Create_TextureNotRegistered)
{
    auto&& resource_mgr = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = kTextureIdMap.Get(Type::Coastal).first;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*resource_mgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{}));

    EXPECT_CALL(*resource_mgr, GetTextureOrDefault)
        .WillRepeatedly(ReturnRef(texture));

    EXPECT_CALL(*resource_mgr, RegisterTexture(StrEq(id), _))
        .WillOnce(ReturnRef(texture));

    auto plot = OpenLabora::plot::create(Type::Coastal, sf::Vector2f{},
                                         resource_mgr);
}

TEST(PlotTests, Create_TextureIsRegistered)
{
    auto&& resource_mgr = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = kTextureIdMap.Get(Type::Coastal).first;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*resource_mgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{ texture }));

    EXPECT_CALL(*resource_mgr, GetTextureOrDefault)
        .Times(0);

    EXPECT_CALL(*resource_mgr, RegisterTexture)
        .Times(0);

    auto plot = OpenLabora::plot::create(Type::Coastal, sf::Vector2f{},
                                         resource_mgr);
}

TEST(PlotTests, CreateCentralInitial_TextureNotRegistered)
{
    auto&& resource_mgr = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = OpenLabora::plot::kCentralInitAltTextureName;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*resource_mgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{}));

    EXPECT_CALL(*resource_mgr, GetTextureOrDefault)
        .WillRepeatedly(ReturnRef(texture));

    EXPECT_CALL(*resource_mgr, RegisterTexture(StrEq(id), _))
        .WillOnce(ReturnRef(texture));

    auto plot = OpenLabora::plot::createCentralInitial(sf::Vector2f{},
                                                       resource_mgr,
                                                       true);
}

TEST(PlotTests, CreateCentralInitial_TextureIsRegistered)
{
    auto&& resource_mgr = std::make_shared<RMM>(std::filesystem::path{});
    auto&& id = OpenLabora::plot::kCentralInitAltTextureName;
    auto&& texture = sf::Texture{};

    EXPECT_CALL(*resource_mgr, GetTexture(StrEq(id)))
        .WillOnce(Return(RMM::OptionalTextureRef{ texture }));

    EXPECT_CALL(*resource_mgr, GetTextureOrDefault)
        .Times(0);

    EXPECT_CALL(*resource_mgr, RegisterTexture)
        .Times(0);

    auto plot = OpenLabora::plot::createCentralInitial(sf::Vector2f{},
                                                       resource_mgr,
                                                       true);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
