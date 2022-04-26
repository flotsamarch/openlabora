#include <cassert>
#include <array>
#include <algorithm>
#include <stdexcept>
#include "Game/Plot.hpp"

namespace OpenLabora
{

namespace plot
{

void initializeSpriteComponent(Plot&, IResourceManager::Ptr,
                               std::string_view id);

Plot create(Type type, TileSpan span, const sf::Vector2f& position,
            bool alternative, IResourceManager::Ptr res_manager,
            std::string_view id = "")
{
    auto plot = Plot{ position, { span, type, alternative }, {} };
    initializeSpriteComponent(plot, res_manager, id);
    return plot;
}

// Use to create plots during gameplay
Plot create(Type type, const sf::Vector2f& position,
            IResourceManager::Ptr res_manager,
            bool alternative)
{
    const auto spans = kPlotTypeToSpans.Get(type);
    return create(type, alternative ? spans.first : spans.second,
                  position, alternative, res_manager);
};

// NOT the same as create(Type::Coastal, ...) - Uses special spans
Plot createCentralInitial(const sf::Vector2f& position,
                          IResourceManager::Ptr res_manager,
                          bool alternative)
{
    const auto span =
        alternative ? kInitialCentralPlotSpan : kInitialCentralPlotAltSpan;

    const auto id =
        alternative ? kCentralInitTextureName : kCentralInitAltTextureName;

    return create(Type::Central, span, position, alternative, res_manager, id);
};

void initializeSpriteComponent(Plot& plot, IResourceManager::Ptr res_manager,
                               std::string_view id)
{
    auto&& plot_component = ecs::getComponent<PlotComponent>(plot);
    auto&& position = ecs::getComponent<PositionComponent>(plot);
    auto&& sprite_component = ecs::getComponent<SpriteComponent>(plot);

    const auto type = plot_component.GetType();

    const auto ids = kTextureIdMap.Get(type);

    if (id.empty()) {
        id = plot_component.IsAlternative() ? ids.first : ids.second;
    }

    sprite_component.SetPosition(position.position);

    auto&& stored_texture = res_manager->GetTexture(id);
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
                auto&& texture = res_manager->GetTextureOrDefault(texture_name);
                sprite.setTexture(texture);
                render_texture.draw(sprite);
                sprite.move({tile::kTileWidth, 0.f});
            }
        }

        auto&& registered_texture =
            res_manager->RegisterTexture(id, render_texture.getTexture());
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

} // namespace OpenLabora
