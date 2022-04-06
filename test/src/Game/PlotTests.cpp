#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Game/Plot.hpp"
#include "Resource/IResourceManagerMock.hpp"

namespace Test
{
using ::testing::_;
using ::testing::ReturnRef;
using ::OpenLabora::Plot;
using Type = Plot::PlotType;

class PlotTests : public ::testing::Test
{
protected:
    IResourceManagerMock::Ptr mResManager =
        std::make_shared<IResourceManagerMock>();

    sf::Texture mTexture;

public:
    virtual ~PlotTests() {};

    PlotTests()
    {
        mTexture.create(1u, 1u);

        ON_CALL(*mResManager, GetTextureByName(_))
            .WillByDefault(ReturnRef(mTexture));

    }
};

TEST_F(PlotTests, ConstructionCentral)
{
    EXPECT_CALL(*mResManager, GetTextureByName(_))
        .Times(5 * 2)
        .WillRepeatedly(ReturnRef(mTexture));

    EXPECT_NO_FATAL_FAILURE(Plot(Plot::kCentralPlot, mResManager));
    ASSERT_NO_FATAL_FAILURE(Plot(Plot::kCentralPlotAlt, mResManager));
}

TEST_F(PlotTests, ConstructionSide)
{
    EXPECT_CALL(*mResManager, GetTextureByName(_))
        .Times(2 * 3)
        .WillRepeatedly(ReturnRef(mTexture));

    EXPECT_NO_FATAL_FAILURE(Plot(Plot::kCoastalPlot, mResManager));
    EXPECT_NO_FATAL_FAILURE(Plot(Plot::kMountainPlotTop, mResManager));
    ASSERT_NO_FATAL_FAILURE(Plot(Plot::kMountainPlotBottom, mResManager));
}

TEST_F(PlotTests, GetType)
{
    const auto central = Plot{ Plot::kCentralPlot, mResManager };
    const auto central_alt = Plot{ Plot::kCentralPlotAlt, mResManager };
    const auto coastal = Plot{ Plot::kCoastalPlot, mResManager };
    const auto mountain_top = Plot{ Plot::kMountainPlotTop, mResManager };
    const auto mountain_bottom = Plot{ Plot::kMountainPlotBottom, mResManager };

    EXPECT_EQ(central.GetType(), Type::Central);
    EXPECT_EQ(central_alt.GetType(), Type::Central);
    EXPECT_EQ(coastal.GetType(), Type::Coastal);
    EXPECT_EQ(mountain_top.GetType(), Type::Mountain);
    ASSERT_EQ(mountain_bottom.GetType(), Type::Mountain);
}

TEST_F(PlotTests, GetTileCount)
{
    const auto central = Plot{ Plot::kCentralPlot, mResManager };
    const auto central_alt = Plot{ Plot::kCentralPlotAlt, mResManager };
    const auto coastal = Plot{ Plot::kCoastalPlot, mResManager };
    const auto mountain_top = Plot{ Plot::kMountainPlotTop, mResManager };
    const auto mountain_bottom = Plot{ Plot::kMountainPlotBottom, mResManager };

    EXPECT_EQ(central.GetTileCount(),
              Plot::GetPlotWidthTileCount(central.GetType()));
    EXPECT_EQ(central_alt.GetTileCount(),
              Plot::GetPlotWidthTileCount(central_alt.GetType()));
    EXPECT_EQ(coastal.GetTileCount(),
              Plot::GetPlotWidthTileCount(coastal.GetType()));
    EXPECT_EQ(mountain_top.GetTileCount(),
              Plot::GetPlotWidthTileCount(mountain_top.GetType()));
    ASSERT_EQ(mountain_bottom.GetTileCount(),
              Plot::GetPlotWidthTileCount(mountain_bottom.GetType()));
}

TEST(PlotStaticMethodsTests, GetPlotWidthTileCount)
{
    EXPECT_EQ(Plot::GetPlotWidthTileCount(Type::Central), 5u);
    EXPECT_EQ(Plot::GetPlotWidthTileCount(Type::Coastal), 2u);
    ASSERT_EQ(Plot::GetPlotWidthTileCount(Type::Mountain), 2u);
}

// TODO: Test GetTileInfo method when it is used

TEST(PlotOperatorsTest, OperatorPreincrement)
{
    constexpr auto begin = static_cast<size_t>(Type::Begin);
    constexpr auto end = static_cast<size_t>(Type::End);
    constexpr auto delta = end - begin;
    auto type = Type::Begin;

    for (size_t i{ 0 }; i < delta; ++i, ++type) {};

    ASSERT_EQ(type, Type::End);
}

TEST_F(PlotTests, EntityTransformations)
{
    constexpr auto offset_x = 10.4f;
    constexpr auto offset_y = 11.4f;
    constexpr auto position_x = 150.15f;
    constexpr auto position_y = 152.15f;
    auto plot_1 = Plot{ Plot::kCentralPlot, mResManager };
    auto plot_2 = Plot{ Plot::kCentralPlot, mResManager };

    ASSERT_FLOAT_EQ(plot_1.GetPosition().x, 0.f);
    ASSERT_FLOAT_EQ(plot_1.GetPosition().y, 0.f);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().x, 0.f);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().y, 0.f);

    plot_1.Move(offset_x, offset_y);
    plot_2.Move(sf::Vector2f{ offset_x, offset_y });

    ASSERT_FLOAT_EQ(plot_1.GetPosition().x, offset_x);
    ASSERT_FLOAT_EQ(plot_1.GetPosition().y, offset_y);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().x, offset_x);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().y, offset_y);

    plot_1.SetPosition(position_x, position_y);
    plot_2.SetPosition(sf::Vector2f{ position_x, position_y });

    ASSERT_FLOAT_EQ(plot_1.GetPosition().x, position_x);
    ASSERT_FLOAT_EQ(plot_1.GetPosition().y, position_y);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().x, position_x);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().y, position_y);

    plot_1.Move(offset_x, offset_y);
    plot_2.Move(sf::Vector2f{ offset_x, offset_y });

    ASSERT_FLOAT_EQ(plot_1.GetPosition().x, offset_x + position_x);
    ASSERT_FLOAT_EQ(plot_1.GetPosition().y, offset_y + position_y);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().x, offset_x + position_x);
    ASSERT_FLOAT_EQ(plot_2.GetPosition().y, offset_y + position_y);
}

TEST_F(PlotTests, EntityBounds)
{
    constexpr auto offset_x = 10.4f;
    constexpr auto offset_y = 11.4f;
    auto plot = Plot{ Plot::kCentralPlot, mResManager };

    auto bounds = plot.GetLocalBounds();
    EXPECT_EQ(bounds.width, plot.GetTileCount() * OpenLabora::Tile::kTileWidth);
    EXPECT_EQ(bounds.height, OpenLabora::Tile::kTileHeight);
    ASSERT_EQ(bounds, plot.GetGlobalBounds());

    plot.Move(offset_x, offset_y);
    bounds = plot.GetGlobalBounds();
    EXPECT_EQ(bounds.width, plot.GetTileCount() * OpenLabora::Tile::kTileWidth);
    EXPECT_EQ(bounds.height, OpenLabora::Tile::kTileHeight);
    EXPECT_EQ(bounds.left, offset_x);
    ASSERT_EQ(bounds.top, offset_y);
}

} // namespace Test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
