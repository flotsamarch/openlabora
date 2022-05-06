#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game/Components/PlayfieldComponent.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace Test
{

using OpenLabora::PlayfieldComponent;
using OpenLabora::plot::Type;
using ResManagerPtr = IResourceManagerMock::Ptr;
using OpenLabora::plot::create;
using ::testing::Return;

class ResManagerConfig : public ::testing::Test
{
    using RMM = IResourceManagerMock;
protected:
    ResManagerPtr mResManager{ std::make_shared<RMM>(std::filesystem::path{}) };
    sf::Texture mTexture{};

public:
    ResManagerConfig()
    {
        ON_CALL(*mResManager, GetTexture)
            .WillByDefault(Return(mTexture));
    }
};

class PlayfieldComponentTests : public ResManagerConfig
{
protected:
    PlayfieldComponent mPlayfieldComponent{ {}, mResManager };
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
        const auto plot = create(type, {}, mResManager);

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
        const auto plot = create(type, {}, mResManager);

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
            auto plot = create(type, {}, mResManager);
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
            auto plot = create(type, {}, mResManager);
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
        auto plot = create(type, {}, mResManager);
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
