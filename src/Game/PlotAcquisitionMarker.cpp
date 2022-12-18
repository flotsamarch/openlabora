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

#include "Game/PlotAcquisitionMarker.hpp"
#include "ECS/MassAssignComponents.hpp"
#include "Game/Components/PlotAcquireInfoComponent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/SelectableComponent.hpp"
#include "Game/Components/SignalComponent.hpp"
#include "Game/Components/InteractionAreaComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"

namespace open_labora
{

namespace plot_acquisition_marker
{

using RectAreaComponent = RectangularInteractionAreaComponent;

Entity create(RegistryRef registry,
              lot::Type lot_type,
              bool does_add_to_top,
              IResourceManager::Ptr resource_mgr)
{
    auto marker = registry.CreateEntity();

    MassAssignComponents{ marker }
        .Assign<PositionComponent>()
        .Assign<RectAreaComponent>()
        .Assign<SelectableComponent>()
        .Assign<SpriteComponent>()
        .Assign<PlotAcquireInfoComponent>(lot_type, does_add_to_top);

    auto&& signals = marker.AssignComponent<SignalComponent>();

    initilizeSpriteComponent(marker, resource_mgr);

    auto on_enter = [marker] () mutable
    {
        auto&& selectable = marker.GetComponent<SelectableComponent>();
        auto&& sprite = marker.GetComponent<SpriteComponent>();
        selectable.Enter();
        sprite.SetColor(kHalfTransparent);
    };

    auto on_out = [marker] () mutable
    {
        auto&& selectable = marker.GetComponent<SelectableComponent>();
        auto&& sprite = marker.GetComponent<SpriteComponent>();
        selectable.Leave();
        if (!selectable.IsSelected()) {
            sprite.SetColor(sf::Color::Transparent);
        }
    };

    auto on_selected = [marker] () mutable
    {
        auto&& selectable = marker.GetComponent<SelectableComponent>();
        selectable.Select();
    };

    auto on_deselected = [marker, on_out] () mutable
    {
        auto&& selectable = marker.GetComponent<SelectableComponent>();
        selectable.Deselect();
        on_out();
    };

    signals.Connect(signals::kOnSelect, on_selected);
    signals.Connect(signals::kOnDeselect, on_deselected);
    signals.Connect(signals::kOnEnter, on_enter);
    signals.Connect(signals::kOnLeave, on_out);

    on_out();

    return marker;
}

void setPosition(Entity marker, const Vector2f& position)
{
    assert(marker.HasComponent<PositionComponent>());
    assert(marker.HasComponent<SpriteComponent>());

    auto&& marker_position = marker.GetComponent<PositionComponent>();
    auto&& sprite = marker.GetComponent<SpriteComponent>();

    marker_position = position;
    sprite.SetPosition(position);
}

void setInteractiveRect(Entity marker,
                        const Vector2f& offset,
                        const Vector2f& size)
{
    assert(marker.HasComponent<RectAreaComponent>());

    const auto rect = sf::RectangleShape{ size };
    auto&& area = marker.GetComponent<RectAreaComponent>();
    area.SetOffset(offset);
    area.SetShape(rect);
}

lot::Type getLotType(Entity marker)
{
    assert(marker.HasComponent<PlotAcquireInfoComponent>());

    auto&& acquire_info = marker.GetComponent<PlotAcquireInfoComponent>();
    return acquire_info.lot_type;
}

Vector2f getSize(lot::Type lot_type)
{
    const auto tile_count = lot::getTileCount(lot_type);
    const auto lot_count = static_cast<int>(plot::getLotCount(lot_type));
    const auto marker_width = static_cast<float>(tile_count * tile::kTileWidth);
    const auto marker_height = static_cast<float>(lot_count * tile::kTileHeight);

    return{ marker_width, marker_height };
}

void initilizeSpriteComponent(Entity marker,
                              IResourceManager::Ptr resource_mgr)
{

    assert(marker.HasComponent<PlotAcquireInfoComponent>());
    assert(marker.HasComponent<SpriteComponent>());

    auto&& plot_params = marker.GetComponent<PlotAcquireInfoComponent>();
    auto&& sprite = marker.GetComponent<SpriteComponent>();
    auto&& texture_id = getTextures(plot_params.lot_type)[0];

    const auto lot_type = plot_params.lot_type;
    auto marker_size = static_cast<Vector2u>(getSize(lot_type));

    sprite.SetRect(sf::IntRect{ { 0, 0 }, static_cast<Vector2i>(marker_size) });

    auto&& stored_texture = resource_mgr->GetTexture(texture_id);
    if (!stored_texture) {
        auto render_texture = RenderTexture{};
        render_texture.create(marker_size.x, marker_size.y);

        auto lots = plot::getPlots(lot_type)[0];
        for (auto offset_y{ 0.f }; auto&& lot : lots) {
            auto lot_sprite = lot::getSprite(lot_type, lot, resource_mgr);
            lot_sprite.setPosition({0.f, offset_y});
            render_texture.draw(lot_sprite);
            offset_y += tile::kTileHeight;
        }

        render_texture.display();

        auto&& registered_texture =
            resource_mgr->StoreTexture(texture_id, render_texture.getTexture());
        sprite.SetTexture(registered_texture);
        return;
    }

    sprite.SetTexture(stored_texture.value());
}

} // namespace plot_acquisition_marker

} // namespace open_labora
