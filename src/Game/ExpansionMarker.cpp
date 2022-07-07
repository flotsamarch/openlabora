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
#include "Resource/IResourceManager.hpp"
#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

namespace marker
{

void setPosition(ExpansionMarker& marker, const sf::Vector2f& position)
{
    auto&& position_cmpnt = ecs::getComponent<PositionComponent>(marker);
    auto&& marker_cmpnt = ecs::getComponent<ExpansionMarkerComponent>(marker);
    auto&& sprite_cmpnt = ecs::getComponent<SpriteComponent>(marker);

    position_cmpnt.position = position;
    marker_cmpnt.SetPlotPositions(position);
    sprite_cmpnt.SetPosition(position);
}

void setInteractiveRect(ExpansionMarker& marker,
                        const sf::Vector2f& offset,
                        const sf::Vector2f& size)
{
    using RectAreaCmpnt = RectangleInteractionAreaComponent;
    auto&& area_cmpnt = ecs::getComponent<RectAreaCmpnt>(marker);
    const auto rect = sf::RectangleShape{ size };

    area_cmpnt.SetOffset(offset);
    area_cmpnt.SetShape(rect);
}

void initilizeSpriteComponent(ExpansionMarker::Ptr,
                              IResourceManager::Ptr,
                              std::string_view id = "");

ExpansionMarker::Ptr create(Type marker_type,
                            plot::Type plot_type,
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
    auto&& selectable_cmpnt = ecs::getComponent<SelectableComponent>(*marker);

    auto on_enter = [&sprite, &selectable_cmpnt]
    {
        selectable_cmpnt.Enter();
        sprite.SetColor(marker::kHalfTransparent);
    };

    auto on_out = [&sprite, &selectable_cmpnt]
    {
        selectable_cmpnt.Leave();
        if (!selectable_cmpnt.IsSelected()) {
            sprite.SetColor(sf::Color::Transparent);
        }
    };

    auto on_selected = [&selectable_cmpnt] { selectable_cmpnt.Select(); };

    auto on_deselected = [&selectable_cmpnt, on_out]
    {
        selectable_cmpnt.Deselect();
        on_out();
    };

    signals.Connect(signals::kOnSelect, on_selected);
    signals.Connect(signals::kOnDeselect, on_deselected);
    signals.Connect(signals::kOnEnter, on_enter);
    signals.Connect(signals::kOnLeave, on_out);

    marker::setPosition(*marker, {});
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

    const auto position = position_component.position;
    sprite_component.SetPosition(position);
    sprite_component.SetRect(sf::IntRect(0, 0, marker_width, marker_height));

    auto&& stored_texture = resource_mgr->GetTexture(id);
    if (!stored_texture) {
        auto&& plot_alt = marker.GetPlots().second.get();
        auto&& plot_sprite = ecs::getComponent<SpriteComponent>(plot);
        auto plot_alt_sprite = ecs::getComponent<SpriteComponent>(plot_alt);

        auto render_texture = sf::RenderTexture{};
        const auto size = sf::Vector2f{ static_cast<float>(marker_width),
                                        static_cast<float>(marker_height) };
        const auto view_rect = sf::FloatRect{ position, size };

        render_texture.create(marker_width, marker_height);
        render_texture.setView(sf::View{ view_rect });
        render_texture.draw(plot_sprite.GetDrawableObject());
        if (!isCentral) {
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
    bool shift_upper = false;
    bool shift_lower = false;

    auto plots = [&pf_component, &shift_upper, &shift_lower, type] {
        auto plots = pf_component.GetPlots(type);
        if (plots.IsEmpty()) {
            return pf_component.GetPlots(plot::Type::Central);
        }

        if (type != plot::Type::Central) {
            shift_upper = true;
        }
        shift_lower = true;
        return plots;
    } ();

    using PosComp = PositionComponent;
    auto position_upper = ecs::getComponent<PosComp>(*plots.begin()).position;
    position_upper.x = playfield::getPlotStripXOffset(type);
    position_upper.y -= shift_upper ? 2 * tile::kTileHeight : tile::kTileHeight;

    auto position_lower = ecs::getComponent<PosComp>(*--plots.end()).position;
    position_lower.x = position_upper.x;
    position_lower.y += shift_lower ? tile::kTileHeight : 0.f;
    return { position_upper, position_lower };
}

} // namespace marker

bool entityHandleEvent(ExpansionMarker::Ptr marker,
                       GameController::Ptr controller,
                       const sf::Event& event)
{
    using RectAreaComponent = RectangleInteractionAreaComponent;
    auto&& selectable = ecs::getComponent<SelectableComponent>(*marker);
    auto&& signals = ecs::getComponent<SignalComponent>(*marker);
    auto&& position_cmpnt = ecs::getComponent<PositionComponent>(*marker);
    auto&& interaction_area = ecs::getComponent<RectAreaComponent>(*marker);

    const auto mouse_world_pos = controller->GetModel()->GetWorldMousePosition();
    const auto local_mouse_pos = mouse_world_pos - position_cmpnt.position;
    const bool is_mouse_over = interaction_area.IsPointInArea(local_mouse_pos);
    const bool has_been_entered = selectable.HasBeenEntered();
    const bool is_selected = selectable.IsSelected();

    switch (event.type) {
    case sf::Event::MouseMoved: {
        if (is_mouse_over && !has_been_entered) {
            signals.Emit(signals::kOnEnter);
        } else if (!is_mouse_over && has_been_entered) {
            signals.Emit(signals::kOnLeave);
        }
        return false;
    }
    case sf::Event::MouseButtonPressed: {
        if (event.mouseButton.button != sf::Mouse::Left) {
            return false;
        }

        if (!has_been_entered && is_selected) {
            signals.Emit(signals::kOnDeselect);
            return false;
        }
        return false;
    }
    case sf::Event::MouseButtonReleased: {
        if (event.mouseButton.button != sf::Mouse::Left) {
            return false;
        }

        if (has_been_entered && !is_selected) {
            signals.Emit(signals::kOnSelect);
            return true;
        }

        return false;
    }
    default: {}
    }

    return false;
}

void entityUpdate(ExpansionMarker::Ptr marker,
                  GameController::Ptr controller,
                  [[maybe_unused]]float update_delta_seconds)
{
    const auto& sprite_cmpnt = ecs::getComponent<SpriteComponent>(*marker);
    controller->AddDrawableObject(sprite_cmpnt.GetDrawableObject());
}

} // namespace OpenLabora
