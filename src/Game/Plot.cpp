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

#include <cassert>
#include <array>
#include <algorithm>
#include "Game/Plot.hpp"

namespace open_labora
{

namespace plot
{

void setPosition(Plot& plot, const sf::Vector2f& position, bool needs_shift)
{
    auto&& plot_cmpnt = ecs::getComponent<PlotComponent>(plot);
    auto&& position_cmpnt = ecs::getComponent<PositionComponent>(plot);
    auto&& sprite_cmpnt = ecs::getComponent<SpriteComponent>(plot);

    auto final_position = [type = plot_cmpnt.GetType(), &position, needs_shift]
    {
        if (needs_shift && type != plot::Type::Central) {
            return position + sf::Vector2f{0.f, tile::kTileHeight};
        }
            return position;
    } ();

    position_cmpnt.position = final_position;
    sprite_cmpnt.SetPosition(final_position);
}

void initializeSpriteComponent(Plot&, IResourceManager::Ptr,
                               std::string_view id);

Plot create(Type type, TileSpan span, const sf::Vector2f& position,
            bool alternative, IResourceManager::Ptr resource_mgr,
            std::string_view id = "")
{
    auto plot = Plot{ position, { span, type, alternative }, {} };
    initializeSpriteComponent(plot, resource_mgr, id);
    return plot;
}

// Use to create plots during gameplay
Plot create(Type type, const sf::Vector2f& position,
            IResourceManager::Ptr resource_mgr,
            bool alternative)
{
    const auto spans = kPlotTypeToSpans.Get(type);
    return create(type, alternative ? spans.second : spans.first,
                  position, alternative, resource_mgr);
};

// NOT the same as create(Type::Coastal, ...) - Uses special spans
Plot createCentralInitial(const sf::Vector2f& position,
                          IResourceManager::Ptr resource_mgr,
                          bool alternative)
{
    const auto span =
        alternative ? kInitialCentralPlotAltSpan : kInitialCentralPlotSpan;

    const auto id =
        alternative ? kCentralInitAltTextureName : kCentralInitTextureName;

    return create(Type::Central, span, position, alternative, resource_mgr, id);
};

void initializeSpriteComponent(Plot& plot,
                               IResourceManager::Ptr resource_mgr,
                               std::string_view id)
{
    auto&& plot_component = ecs::getComponent<PlotComponent>(plot);
    auto&& pos_component = ecs::getComponent<PositionComponent>(plot);
    auto&& sprite_component = ecs::getComponent<SpriteComponent>(plot);

    const auto type = plot_component.GetType();

    if (id.empty()) {
        const auto ids = kTextureIdMap[type];
        if (ids.size() > 1) {
            id = plot_component.IsAlternative() ? ids[1] : ids[0];
        } else {
            id = ids[0];
        }
    }

    sprite_component.SetPosition(pos_component.position);

    auto&& stored_texture = resource_mgr->GetTexture(id);
    if (!stored_texture) {
        const auto width = kPlotWidthTileCount.Get(type) * tile::kTileWidth;

        auto render_texture = sf::RenderTexture{};
        render_texture.create(width, tile::kTileHeight);
        render_texture.clear();

        {
            auto sprite = sf::Sprite{};
            sprite.setPosition({ 0.f, 0.f });
            sprite.setTextureRect({ 0, 0, tile::kTileWidth, tile::kTileHeight });

            for (auto&& item : plot_component.GetTiles()) {
                const auto texture_name = tile::kTileToTextureMap.Get(item);
                auto&& texture = resource_mgr->GetTextureOrDefault(texture_name);
                sprite.setTexture(texture);
                render_texture.draw(sprite);
                sprite.move({tile::kTileWidth, 0.f});
            }
        }

        render_texture.display();
        auto&& registered_texture =
            resource_mgr->RegisterTexture(id, render_texture.getTexture());
        sprite_component.SetTexture(registered_texture, true);
        return;
    }
    sprite_component.SetTexture(stored_texture.value(), true);
}

} // namespace plot

#if 0 // TODO: Reimplement Build Mode
float Plot::GetOffsetXForPlotType(PlotType type)
{
    assert(type >= PlotType::Begin && type < PlotType::End);
    auto offset{ 0u };
    for (auto i = PlotType::Begin; i < type && i <PlotType::End; ++i) {
        offset += Tile::kTileWidth * GetPlotWidthTileCount(i);
    }
    return static_cast<float>(offset);
}

Plot::OptionalTileInfo
Plot::GetTileInfoUnderPoint(const sf::Vector2f& point) const
{
    if (!GetGlobalBounds().contains(point)) {
        return std::nullopt;
    }

    auto index = (point.y - GetPosition().y) / Tile::kTileWidth;
    return mTiles[static_cast<size_t>(index)].GetTileInfo();
}
#endif

} // namespace open_labora
