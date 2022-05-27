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

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "Game/Playfield.hpp"
#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

using TCC = TextureContainerComponent;

namespace playfield
{

Playfield::Ptr create(IResourceManager::Ptr resource_mgr,
                                  const sf::Vector2f& init_pos)
{
    using PC = PlayfieldComponent;
    auto playfield = std::make_shared<Playfield>(init_pos,
                                                 PC{ init_pos, resource_mgr },
                                                 TCC{},
                                                 SpriteComponent{});

    auto&& sprite = ecs::getComponent<SpriteComponent>(*playfield);
    sprite.SetPosition(init_pos);

    return playfield;
}

Playfield::Ptr create(IResourceManager::Ptr resource_mgr,
                                  float initial_x, float initial_y)
{ return create(resource_mgr, { initial_x, initial_y }); }

} // namespace playfield

bool entityHandleEvent([[maybe_unused]]Playfield::Ptr entity,
                       [[maybe_unused]]GameController::Ptr controller,
                       [[maybe_unused]]const sf::Event& event)
{
    return false;
}

void entityUpdate(Playfield::Ptr entity,
                  [[maybe_unused]]float update_delta_seconds,
                  GameController::Ptr controller)
{
    auto&& playfield = ecs::getComponent<PlayfieldComponent>(*entity);
    auto&& ground_texture = ecs::getComponent<TCC>(*entity);
    auto&& sprite = ecs::getComponent<SpriteComponent>(*entity);

    if (ground_texture.NeedsUpdate()) {
        auto texture = sf::RenderTexture{};
        const auto pf_width = tile::kTileWidth * playfield::kMaxFieldWidth;
        const auto pf_height = tile::kTileHeight * playfield::kMaxFieldHeight;

        texture.create(pf_width, pf_height);

        for (auto type = plot::Type::Begin; type < plot::Type::End; ++type) {
            auto plots = playfield.GetPlots(type);

            if (plots.IsEmpty()) {
                continue;
            }

            for (auto&& plot : plots) {
                auto&& plot_sprite = ecs::getComponent<SpriteComponent>(plot);
                texture.draw(plot_sprite.GetDrawableObject());
            }
        }

        using Rect = sf::RectangleShape;
        auto rect = Rect(sf::Vector2f(pf_width - 4, pf_height - 4));
        rect.setPosition(2.f, 2.f);
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineThickness(4.f);
        rect.setOutlineColor(sf::Color::Yellow);

        texture.draw(rect);
        texture.display();

        ground_texture.SetTexture(texture.getTexture());
        ground_texture.MarkUpdated(true);
        sprite.SetTexture(ground_texture.GetTexture());
    }

    controller->AddDrawableObject(sprite.GetDrawableObject());
}

} // namespace OpenLabora
