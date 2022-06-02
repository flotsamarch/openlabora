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

#include "Game/ExpansionMarker.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "Resource/IResourceManager.hpp"

namespace OpenLabora
{

namespace marker
{

void initilizeSpriteComponent(ExpansionMarker::Ptr,
                              IResourceManager::Ptr,
                              std::string_view id = "");

ExpansionMarker::Ptr create(Type marker_type,
                            plot::Type plot_type,
                            std::function<void()> on_left_released,
                            IResourceManager::Ptr resource_mgr)
{
    auto plot = plot::create(plot_type, {}, resource_mgr);
    auto plot_alt = plot::create(plot_type, {}, resource_mgr, true);
    auto&& emc = ExpansionMarkerComponent{ marker_type, plot, plot_alt };
    using RIAC = RectangleInteractionAreaComponent;
    auto marker = std::make_shared<ExpansionMarker>(std::move(emc),
                                                    PositionComponent{},
                                                    SelectableComponent{},
                                                    RIAC{},
                                                    SignalComponent{},
                                                    SpriteComponent{});

    auto&& sprite = ecs::getComponent<SpriteComponent>(*marker);
    auto&& signals = ecs::getComponent<SignalComponent>(*marker);

    auto on_out = [&sprite] { sprite.SetColor(sf::Color::Transparent); };
    auto on_enter = [&sprite] { sprite.SetColor(marker::kHalfTransparent); };

    signals.Connect(Signals::OnLeftReleased, on_left_released);
    signals.Connect(Signals::OnMouseEnter, on_enter);
    signals.Connect(Signals::OnMouseLeave, on_out);

    initilizeSpriteComponent(marker, resource_mgr);
    on_out();

    return marker;
}

void initilizeSpriteComponent(ExpansionMarker::Ptr entity,
                              IResourceManager::Ptr resource_mgr,
                              std::string_view id)
{
    auto&& marker = ecs::getComponent<ExpansionMarkerComponent>(*entity);
    auto&& sprite_component = ecs::getComponent<SpriteComponent>(*entity);
    auto&& position_component = ecs::getComponent<PositionComponent>(*entity);

    const auto type = marker.GetPlotType();

    if (id.empty()) {
        const auto& ids = kTextureIdMap[type];
        id = ids[0]; // TODO Handle central plot type case with 2 textures
    }

    auto&& plot = marker.GetPlots().first.get();
    auto&& plot_component = ecs::getComponent<PlotComponent>(plot);

    const bool isCentral = plot_component.GetType() == plot::Type::Central;
    const auto tile_count = plot_component.GetTileCount();

    const auto marker_width = tile_count * tile::kTileWidth;
    const auto marker_height = tile::kTileHeight * (isCentral ? 1u : 2u);

    sprite_component.SetPosition(position_component.position);
    sprite_component.SetRect(sf::IntRect(0, 0, marker_width, marker_height));

    auto&& stored_texture = resource_mgr->GetTexture(id);
    if (!stored_texture) {
        auto&& plot_alt = marker.GetPlots().second.get();
        auto&& plot_sprite = ecs::getComponent<SpriteComponent>(plot);
        auto plot_alt_sprite = ecs::getComponent<SpriteComponent>(plot_alt);

        auto render_texture = sf::RenderTexture{};
        render_texture.create(marker_width, marker_height);
        render_texture.draw(plot_sprite.GetDrawableObject());
        if (!isCentral) {
            plot_alt_sprite.SetPosition({ 0.f, tile::kTileHeight });
            render_texture.draw(plot_alt_sprite.GetDrawableObject());
        }
        render_texture.display();

        auto&& registered_texture =
            resource_mgr->RegisterTexture(id, render_texture.getTexture());
        sprite_component.SetTexture(registered_texture);
        return;
    }
    sprite_component.SetTexture(stored_texture.value());
}

MarkerPositions GetBoundaryMarkerPositions(plot::Type type,
                                           Playfield::PtrConst playfield)
{
    auto&& pf_component = ecs::getComponent<PlayfieldComponent>(*playfield);
    bool shift_lower = false;

    auto plots = [&pf_component, &shift_lower, type] {
        auto plots = pf_component.GetPlots(type);
        if (plots.IsEmpty()) {
            return pf_component.GetPlots(plot::Type::Central);
        }
        shift_lower = true;
        return plots;
    } ();

    using PosComp = PositionComponent;
    auto position_upper = ecs::getComponent<PosComp>(*plots.begin()).position;
    position_upper.x = playfield::getPlotStripXOffset(type);
    position_upper.y -= tile::kTileHeight;

    auto position_lower = ecs::getComponent<PosComp>(*--plots.end()).position;
    position_lower.x = position_upper.x;
    position_lower.y += shift_lower ? tile::kTileHeight : 0.f;
    return { position_upper, position_lower };
}

bool handleEvent(ExpansionMarker::Ptr marker,
                 const sf::Vector2f& mouse_world_pos,
                 const sf::Event& event)
{
    using RectAreaComponent = RectangleInteractionAreaComponent;
    auto&& selectable = ecs::getComponent<SelectableComponent>(*marker);
    auto&& signals = ecs::getComponent<SignalComponent>(*marker);
    auto&& position_cmpnt = ecs::getComponent<PositionComponent>(*marker);
    auto&& interaction_area = ecs::getComponent<RectAreaComponent>(*marker);

    const auto local_mouse_pos = mouse_world_pos - position_cmpnt.position;
    const bool is_mouse_over = interaction_area.IsPointInArea(local_mouse_pos);
    const bool has_been_entered = selectable.HasBeenEntered();
    const bool is_selected = selectable.IsSelected();

    switch (event.type) {
    case sf::Event::MouseMoved: {
        if (is_mouse_over && !has_been_entered) {
            selectable.Enter();
            signals.Emit(Signals::OnMouseEnter);
        } else if (!is_mouse_over && has_been_entered) {
            selectable.Leave();
            signals.Emit(Signals::OnMouseLeave);
        }
        return false;
    }
    case sf::Event::MouseButtonPressed: {
        if (event.mouseButton.button != sf::Mouse::Left) {
            return false;
        }

        if (has_been_entered && !is_selected) {
            selectable.Select();
            signals.Emit(Signals::OnLeftPressed);
            return true;
        }

        if (!has_been_entered && is_selected) {
            selectable.Deselect();
            return false;
        }
        return false;
    }
    case sf::Event::MouseButtonReleased: {
        if (event.mouseButton.button != sf::Mouse::Left) {
            return false;
        }

        if (has_been_entered && is_selected) {
            signals.Emit(Signals::OnLeftReleased);
            return true;
        }
        return false;
    }
    default: {}
    }

    return false;
}

} // namespace marker

} // namespace OpenLabora
