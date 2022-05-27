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
#include "Game/Components/PlayfieldComponent.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace Test
{

using OpenLabora::PlayfieldComponent;
using OpenLabora::plot::Type;
using OpenLabora::plot::create;
using ::testing::Return;

class ResourceMgrConfig : public ::testing::Test
{
    using RMM = IResourceManagerMock;
protected:
    RMM::Ptr mResourceMgr{ std::make_shared<RMM>(std::filesystem::path{}) };
    sf::Texture mTexture{};

public:
    ResourceMgrConfig()
    {
        ON_CALL(*mResourceMgr, GetTexture)
            .WillByDefault(Return(mTexture));
    }
};

class PlayfieldComponentTests : public ResourceMgrConfig
{
protected:
    PlayfieldComponent mPlayfieldComponent{ {}, mResourceMgr };
};

TEST_F(PlayfieldComponentTests, Construction)
{
    auto&& plots = mPlayfieldComponent.GetPlots(Type::Central);

    EXPECT_FALSE(plots.IsEmpty());
    EXPECT_EQ(plots.GetSize(), 2);
}

TEST_F(PlayfieldComponentTests, AddPlotToTop)
{
    for (auto type = Type::Begin; type != Type::End; ++type) {
        const auto plot = create(type, {}, mResourceMgr);

        mPlayfieldComponent.AddPlotToTop(plot);
        mPlayfieldComponent.AddPlotToTop(plot);
        mPlayfieldComponent.AddPlotToTop(plot);

        auto&& plots = mPlayfieldComponent.GetPlots(type);

        EXPECT_EQ(plots.GetSize(), 3 + (type == Type::Central ? 2 : 0));
    }
}

TEST_F(PlayfieldComponentTests, AddPlotToBottom)
{
    for (auto type = Type::Begin; type != Type::End; ++type) {
        const auto plot = create(type, {}, mResourceMgr);

        mPlayfieldComponent.AddPlotToBottom(plot);
        mPlayfieldComponent.AddPlotToBottom(plot);
        mPlayfieldComponent.AddPlotToBottom(plot);

        auto&& plots = mPlayfieldComponent.GetPlots(type);

        EXPECT_EQ(plots.GetSize(), 3 + (type == Type::Central ? 2 : 0));
    }
}


TEST_F(PlayfieldComponentTests, AddPlotToTopRvalue)
{
    for (auto type = Type::Begin; type != Type::End; ++type) {
        for (auto i{ 0 }; i < 3; ++i) {
            auto plot = create(type, {}, mResourceMgr);
            mPlayfieldComponent.AddPlotToTop(std::move(plot));
        }

        auto&& plots = mPlayfieldComponent.GetPlots(type);

        EXPECT_EQ(plots.GetSize(), 3 + (type == Type::Central ? 2 : 0));
    }
}

TEST_F(PlayfieldComponentTests, AddPlotToBottomRvalue)
{
    for (auto type = Type::Begin; type != Type::End; ++type) {
        for (auto i{ 0 }; i < 3; ++i) {
            auto plot = create(type, {}, mResourceMgr);
            mPlayfieldComponent.AddPlotToBottom(std::move(plot));
        }

        auto&& plots = mPlayfieldComponent.GetPlots(type);

        EXPECT_EQ(plots.GetSize(), 3 + (type == Type::Central ? 2 : 0));
    }
}

TEST_F(PlayfieldComponentTests, PlotsLimitIsReachable)
{
    constexpr auto over_max = 50u; // Not sure this is a right way to do it

    for (auto type = Type::Begin; type != Type::End; ++type) {
        auto plot = create(type, {}, mResourceMgr);
        bool reached{ false };

        for (auto i{ 0u }; i < over_max; ++i) {
            mPlayfieldComponent.AddPlotToBottom(plot);

            if (mPlayfieldComponent.IsPlotsLimitReached(type)) {
                reached = true;
                break;
            }
        }
        EXPECT_TRUE(reached);
    }
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
