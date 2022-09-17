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

#include "Game/Lot.hpp"

namespace open_labora
{

namespace lot
{

Sprite getSprite(Type type,
                 SubtypeId subtype,
                 IResourceManager::Ptr resource_mgr)
{
    const auto subtype_index = static_cast<size_t>(subtype);
    const auto texture_id = getLotSubtypeTextureNames(type)[subtype_index];
    auto&& stored_texture = resource_mgr->GetTexture(texture_id);

    if (!stored_texture) {
        const auto width = getTileCount(type) * tile::kTileWidth;

        auto render_texture = sf::RenderTexture{};
        render_texture.create(width, tile::kTileHeight);
        render_texture.clear();

        {
            auto sprite = Sprite{};
            sprite.setPosition({ 0.f, 0.f });
            sprite.setTextureRect({ 0, 0, tile::kTileWidth, tile::kTileHeight });

            for (auto&& tile : getLotSubtypes(type)[subtype_index]) {
                const auto texture_name = tile::getTextureName(tile);
                auto&& texture = resource_mgr->GetTextureOrDefault(texture_name);
                sprite.setTexture(texture);
                render_texture.draw(sprite);
                sprite.move({tile::kTileWidth, 0.f});
            }
        }

        render_texture.display();
        auto&& texture = render_texture.getTexture();
        return Sprite{ resource_mgr->StoreTexture(texture_id, texture) };
    }
    return Sprite{ stored_texture.value().get() };
}

} // namespace plot

} // namespace open_labora
