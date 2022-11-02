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

#include "Game/Systems/PlayfieldSystem.hpp"
#include "Game/LotDeque.hpp"
#include "Game/Components/DynamicTextureComponent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/SpriteComponent.hpp"

namespace open_labora
{

PlayfieldSystem::PlayfieldSystem(Registry& registry,
                                 IResourceManager::Ptr resource_mgr)
    : mResourceMgr{ resource_mgr }
{
    constexpr auto central = lot::Type::Central;
    const auto offset_x = static_cast<float>(lot::getOffsetX(central));
    const auto offset_y = static_cast<float>(lot::kHeartlandOffsetY);

    auto entity = lot_deque::create(registry, central, { offset_x, offset_y });
    mLotDeques.emplace(central, entity);

    auto&& deque = entity.GetComponent<LotDequeComponent>();
    deque.AddLotToBottom(lot::kCentralPFFFH);
    deque.AddLotToBottom(lot::kCentralPFFFF);
}

void systemHandleEvent(PlayfieldSystem& system,
                       RegistryRef registry,
                       const DrawEvent&)
{
    auto draw = [resource_mgr = system.GetResourceManager()]
    (Entity entity,
     const LotDequeComponent& deque,
     DynamicTextureComponent& dynamic_texture,
     const PositionComponent& position,
     SpriteComponent& sprite)
    {
        const auto plot_count = static_cast<uint>(deque.GetLotsCount());
        if (!dynamic_texture.NeedsUpdate() || plot_count == 0) {
            return;
        }

        auto render_texture = RenderTexture{};
        const auto type = deque.GetLotType();
        const auto width = tile::kTileWidth * lot::getTileCount(type);
        const auto height = tile::kTileHeight * plot_count;
        const auto width_f = static_cast<float>(width);
        const auto height_f = static_cast<float>(height);
        const auto size = Vector2f{ width_f, height_f };
        const auto view_rect = FloatRect{ { 0.f, 0.f }, size };

        render_texture.create(width, height);
        render_texture.setView(View{ view_rect });

        for (auto i{ 0u }; auto&& variant : deque) {
            auto p_sprite = lot::getSprite(type, variant, resource_mgr);
            const auto offset_y = static_cast<float>(i * tile::kTileHeight);
            p_sprite.setPosition(Vector2f{ 0.f, offset_y });
            render_texture.draw(p_sprite);
            ++i;
        }

        auto rect = RectangleShape({ width_f - 4.f, height_f - 4.f });
        rect.setPosition(2.f, 2.f);
        rect.setFillColor(Color::Transparent);
        rect.setOutlineThickness(4.f);
        rect.setOutlineColor(Color::Yellow);

        render_texture.draw(rect);
        render_texture.display();

        const auto id = entity.GetId();
        const auto name = std::stringstream{} << PlayfieldSystem::kTexturePrefix
                                              << id;

        auto&& texture = render_texture.getTexture();
        auto&& stored_texture = resource_mgr->StoreTexture(name.view(), texture);
        dynamic_texture.SetUpToDate(true);
        sprite.SetTexture(stored_texture, true);
        sprite.SetPosition(position);
    };

    registry.ForJoinedComponents<LotDequeComponent,
                                 DynamicTextureComponent,
                                 PositionComponent,
                                 SpriteComponent>(draw);
}

void systemHandleEvent(PlayfieldSystem& system,
                       RegistryRef registry,
                       const CreatePlotEvent& event)
{
    auto entity = [&deques = system.GetLotDeques(),
                   &event,
                   &registry,
                   position = event.position] () mutable
    {
        if (deques.contains(event.lot_type)) {
            return deques.at(event.lot_type);
        }

        if (event.to_top) {
            position.y += event.plot.size() * tile::kTileHeight;
        }
        auto new_deque = lot_deque::create(registry, event.lot_type, position);
        deques.emplace(event.lot_type, new_deque);

        return new_deque;
    } ();

    auto&& deque = entity.GetComponent<LotDequeComponent>();
    auto&& position = entity.GetComponent<PositionComponent>();
    auto&& dynamic_texture = entity.GetComponent<DynamicTextureComponent>();

    if (event.to_top) {
        auto end = event.plot.rend();
        for (auto it{ event.plot.rbegin() }; it < end; ++it) {
            deque.AddLotToTop(*it);
            position.y -= tile::kTileHeight;
        }
    } else {
        for (auto&& lot : event.plot) {
            deque.AddLotToBottom(lot);
        }
    }
    dynamic_texture.SetUpToDate(false);
}

} // namespace open_labora
