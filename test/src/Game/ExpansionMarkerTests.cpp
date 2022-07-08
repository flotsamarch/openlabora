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
#include "Resource/ResourceManagerDefaultActionTestBase.hpp"
#include "Game/ExpansionMarker.hpp"

namespace test
{

namespace ol = open_labora;

using ExpansionMarkerTests = ResourceManagerDefaultActionTestBase;
using TestBase = ResourceManagerDefaultActionTestBase;
using PlotType = ol::plot::Type;
using MarkerType = ol::marker::Type;

class NamespaceMarkerFreeFunctionsTests : public TestBase
{
protected:
    ol::Playfield::Ptr mPlayfield{ ol::playfield::create(mResourceMgr, {}) };
};

TEST_F(NamespaceMarkerFreeFunctionsTests,
       GetBoundaryMarkerPositions_DefaultCentralAre3TilesApart)
{
    constexpr auto central = PlotType::Central;

    auto&& [upper_pos, lower_pos] =
        ol::marker::GetBoundaryMarkerPositions(central, mPlayfield);

    auto distance = lower_pos - upper_pos;
    EXPECT_FLOAT_EQ(distance.x, 0.f);
    ASSERT_GE(distance.y, ol::tile::kTileHeight * 3.f);
}

TEST_F(NamespaceMarkerFreeFunctionsTests,
       GetBoundaryMarkerPositions_AddingPlotsIncreasesDistance)
{
    using ol::marker::GetBoundaryMarkerPositions;
    using ol::ecs::getComponent;
    constexpr auto central = PlotType::Central;
    auto plot = create(central, {}, mResourceMgr);

    auto&& [upos_before, bpos_before] = GetBoundaryMarkerPositions(central,
                                                                   mPlayfield);
    auto distance_before = bpos_before - upos_before;

    auto&& component = getComponent<ol::PlayfieldComponent>(*mPlayfield);
    component.AddPlotToTop(plot);

    auto&& [upos_after, bpos_after] = GetBoundaryMarkerPositions(central,
                                                                 mPlayfield);
    auto distance_after = bpos_after - upos_after;

    EXPECT_FLOAT_EQ(distance_before.x, 0.f);
    EXPECT_FLOAT_EQ(distance_after.x, 0.f);
    ASSERT_GT(distance_after.y, distance_before.y);
}

TEST_F(NamespaceMarkerFreeFunctionsTests,
       GetBoundaryMarkerPositions_NonCentralMarkersDependOnCentralByDefault)
{
    using ol::marker::GetBoundaryMarkerPositions;
    constexpr auto coastal = PlotType::Coastal;
    constexpr auto central = PlotType::Central;
    constexpr auto tile_h = ol::tile::kTileHeight;

    auto&& [coastal_upos, coastal_bpos] = GetBoundaryMarkerPositions(coastal,
                                                                     mPlayfield);
    auto&& [central_upos, central_bpos] = GetBoundaryMarkerPositions(central,
                                                                     mPlayfield);
    auto offset_x = ol::playfield::getPlotStripXOffset(coastal);

    auto distance_coastal = coastal_bpos - coastal_upos;
    EXPECT_FLOAT_EQ(distance_coastal.x, 0.f);
    EXPECT_GT(distance_coastal.y, tile_h);
    EXPECT_FLOAT_EQ(coastal_upos.x, offset_x);
    EXPECT_FLOAT_EQ(coastal_bpos.x, offset_x);
    EXPECT_FLOAT_EQ(coastal_upos.y, central_upos.y);
    ASSERT_FLOAT_EQ(coastal_bpos.y, central_bpos.y - tile_h);
}

TEST_F(NamespaceMarkerFreeFunctionsTests,
       GetBoundaryMarkerPositions_AddingCentralPlotsIncreasesNonCentralDistance)
{
    using ol::marker::GetBoundaryMarkerPositions;
    using ol::ecs::getComponent;
    constexpr auto central = PlotType::Central;
    constexpr auto coastal = PlotType::Coastal;

    auto plot = ol::plot::create(central, {}, mResourceMgr);

    auto&& [upos_before, bpos_before] = GetBoundaryMarkerPositions(coastal,
                                                                  mPlayfield);
    auto distance_before = bpos_before - upos_before;

    auto&& component = getComponent<ol::PlayfieldComponent>(*mPlayfield);
    component.AddPlotToTop(plot);
    auto&& [upos_after, bpos_after] = GetBoundaryMarkerPositions(coastal,
                                                               mPlayfield);

    auto distance_after = bpos_after - upos_after;

    EXPECT_FLOAT_EQ(distance_before.x, 0.f);
    EXPECT_FLOAT_EQ(distance_after.x, 0.f);
    ASSERT_GT(distance_after.y, distance_before.y);
}

TEST_F(ExpansionMarkerTests, HasNotBeenEnteredByDefault)
{
    auto marker = ol::marker::create(MarkerType::Begin,
                                     PlotType::Begin,
                                     mResourceMgr);

    auto&& selectable = ol::ecs::getComponent<ol::SelectableComponent>(*marker);

    ASSERT_FALSE(selectable.HasBeenEntered());
}

#if 0 // TODO: Make event handling actually testable
TEST_F(ExpansionMarkerTests, EventHandling_Enter)
{
    using open_labora::marker::create;
    using open_labora::marker::handleEvent;
    using open_labora::ecs::getComponent;
    using RectIACmpnt = open_labora::RectangleInteractionAreaComponent;

    const auto mouse_pos = sf::Vector2f{ 1.f, 1.f };
    auto marker = create(MarkerType::Begin, PlotType::Begin, mResourceMgr);
    auto&& selectable = getComponent<ol::SelectableComponent>(*marker);
    auto&& interactive_area = getComponent<RectIACmpnt>(*marker);

    auto shape = sf::RectangleShape{{ 5.f, 5.f }};
    interactive_area.SetShape({ shape });

    sf::Event event;
    event.type = sf::Event::MouseMoved;
    handleEvent(marker, mouse_pos, event);

    ASSERT_TRUE(selectable.HasBeenEntered());
}

TEST_F(ExpansionMarkerTests, EventHandling_EnterThenLeave)
{
    using open_labora::marker::create;
    using open_labora::marker::handleEvent;
    using open_labora::ecs::getComponent;
    using RectIACmpnt = open_labora::RectangleInteractionAreaComponent;

    const auto mouse_pos_in = sf::Vector2f{ 1.f, 1.f };
    const auto mouse_pos_out = sf::Vector2f{ -999.f, -999.f };
    auto marker = create(MarkerType::Begin, PlotType::Begin, mResourceMgr);
    auto&& selectable = getComponent<ol::SelectableComponent>(*marker);
    auto&& interactive_area = getComponent<RectIACmpnt>(*marker);

    auto shape = sf::RectangleShape{{ 5.f, 5.f }};
    interactive_area.SetShape({ shape });

    sf::Event event;
    event.type = sf::Event::MouseMoved;
    handleEvent(marker, mouse_pos_in, event); // Enter
    bool was_entered_first = selectable.HasBeenEntered();

    handleEvent(marker, mouse_pos_out, event); // Leave
    bool was_left = !selectable.HasBeenEntered();

    EXPECT_TRUE(was_entered_first);
    ASSERT_TRUE(was_left);
}

TEST_F(ExpansionMarkerTests, EventHandling_Select)
{
    using open_labora::marker::create;
    using open_labora::marker::handleEvent;
    using open_labora::ecs::getComponent;
    using RectIACmpnt = open_labora::RectangleInteractionAreaComponent;

    const auto mouse_pos = sf::Vector2f{ 1.f, 1.f };
    auto marker = create(MarkerType::Begin, PlotType::Begin, mResourceMgr);
    auto&& selectable = getComponent<ol::SelectableComponent>(*marker);
    auto&& interactive_area = getComponent<RectIACmpnt>(*marker);

    auto shape = sf::RectangleShape{{ 5.f, 5.f }};
    interactive_area.SetShape({ shape });

    sf::Event event;
    event.type = sf::Event::MouseMoved;
    handleEvent(marker, mouse_pos, event); // Enter

    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    bool event_consumed = handleEvent(marker, mouse_pos, event); // Click

    EXPECT_TRUE(event_consumed);
    ASSERT_TRUE(selectable.IsSelected());
}

TEST_F(ExpansionMarkerTests, EventHandling_Deselect)
{
    using open_labora::marker::create;
    using open_labora::marker::handleEvent;
    using open_labora::ecs::getComponent;
    using RectIACmpnt = open_labora::RectangleInteractionAreaComponent;
    const auto mouse_pos_in = sf::Vector2f{ 1.f, 1.f };
    const auto mouse_pos_out = sf::Vector2f{ -999.f, -999.f };
    auto marker = create(MarkerType::Begin, PlotType::Begin, mResourceMgr);
    auto&& selectable = getComponent<ol::SelectableComponent>(*marker);
    auto&& interactive_area = getComponent<RectIACmpnt>(*marker);

    auto shape = sf::RectangleShape{{ 5.f, 5.f }};
    interactive_area.SetShape({ shape });

    sf::Event event;
    event.type = sf::Event::MouseMoved;
    handleEvent(marker, mouse_pos_in, event); // Enter

    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    handleEvent(marker, mouse_pos_in, event); // Click - Select

    bool was_selected = selectable.IsSelected();

    event.type = sf::Event::MouseMoved;
    handleEvent(marker, mouse_pos_out, event); // Leave

    event.type = sf::Event::MouseButtonPressed;
    event.mouseButton.button = sf::Mouse::Left;
    handleEvent(marker, mouse_pos_out, event); // Click - Deselect

    bool no_longer_selected = !selectable.IsSelected();

    EXPECT_TRUE(was_selected);
    ASSERT_TRUE(no_longer_selected);
}

TEST_F(ExpansionMarkerTests, EventHandling_CustomSelect)
{
    using open_labora::marker::create;
    using open_labora::marker::handleEvent;
    using open_labora::ecs::getComponent;
    using open_labora::signals::kOnSelect;
    using RectIACmpnt = open_labora::RectangleInteractionAreaComponent;
    using SignalComponent = open_labora::SignalComponent;

    const auto mouse_pos = sf::Vector2f{ 1.f, 1.f };
    bool acted_upon = false;
    auto act = [&acted_upon] { acted_upon = true; };

    auto marker = create(MarkerType::Begin, PlotType::Begin, mResourceMgr);
    auto&& interactive_area = getComponent<RectIACmpnt>(*marker);
    auto&& signal_cmpnt = getComponent<SignalComponent>(*marker);

    signal_cmpnt.Connect(kOnSelect, act);

    auto shape = sf::RectangleShape{{ 5.f, 5.f }};
    interactive_area.SetShape({ shape });

    sf::Event event;
    event.type = sf::Event::MouseMoved;
    handleEvent(marker, mouse_pos, event); // Enter

    event.type = sf::Event::MouseButtonReleased;
    event.mouseButton.button = sf::Mouse::Left;
    handleEvent(marker, mouse_pos, event); // Released

    ASSERT_TRUE(acted_upon);
}
#endif

TEST_F(ExpansionMarkerTests, SetPosition)
{
    using ol::marker::create;
    using ol::ecs::getComponent;
    using PosCmpnt = ol::PositionComponent;

    constexpr auto x = 31.12345f;
    constexpr auto y = 144.905f;
    auto marker = create(MarkerType::Begin, PlotType::Begin, mResourceMgr);
    auto&& position_cmpnt = getComponent<PosCmpnt>(*marker);
    auto&& sprite_cmpnt = getComponent<ol::SpriteComponent>(*marker);
    auto&& marker_cmpnt = getComponent<ol::ExpansionMarkerComponent>(*marker);
    auto&& plots = marker_cmpnt.GetPlots();
    auto&& plot_position = getComponent<PosCmpnt>(plots.first.get());
    auto&& plot_alt_position = getComponent<PosCmpnt>(plots.second.get());

    ol::marker::setPosition(*marker, {x, y});

    EXPECT_FLOAT_EQ(position_cmpnt.position.x, x);
    EXPECT_FLOAT_EQ(position_cmpnt.position.y, y);
    EXPECT_FLOAT_EQ(sprite_cmpnt.GetPosition().x, x);
    EXPECT_FLOAT_EQ(sprite_cmpnt.GetPosition().y, y);
    EXPECT_GT(plot_position.position.x, 0.f);
    EXPECT_GT(plot_position.position.y, 0.f);
    EXPECT_GT(plot_alt_position.position.x, 0.f);
    ASSERT_GT(plot_alt_position.position.y, 0.f);
}

TEST_F(ExpansionMarkerTests, SetInteractiveRect)
{
    using ol::marker::create;
    auto marker = create(MarkerType::Begin, PlotType::Begin, mResourceMgr);
    auto&& selectable = ol::ecs::getComponent<ol::SelectableComponent>(*marker);

    ASSERT_FALSE(selectable.HasBeenEntered());
}


} // namespace test

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
