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

#ifndef PLAYFIELD_HPP_
#define PLAYFIELD_HPP_

#include <memory>
#include <numeric>
#include <algorithm>
#include <SFML/Window/Event.hpp>
#include "ECS/ComponentContainer.hpp"
#include "Components/ImmobileComponent.hpp"
#include "Components/TextureContainerComponent.hpp"
#include "Components/PlayfieldComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Resource/IResourceManager.hpp"

namespace open_labora
{

class GameController;

using Playfield = ComponentContainer<ImmobileComponent,
                                     PlayfieldComponent,
                                     TextureContainerComponent,
                                     SpriteComponent>;

namespace playfield
{

struct PlotCreationParams
{
    plot::PlotsPair plots;
    bool add_to_top;
    bool alt_required;
};

std::function<void()>
MakePlotCreationDelegate(Playfield::Ptr,
                         std::function<PlotCreationParams()> get_params);

Playfield::Ptr create(IResourceManager::Ptr,
                      const sf::Vector2f& initial_position);

Playfield::Ptr create(IResourceManager::Ptr,
                      float initial_x, float initial_y);

constexpr float getPlotStripXOffset(plot::Type type)
{
    auto begin = plot::kPlotWidthTileCount.cbegin();
    auto end = plot::kPlotWidthTileCount.cend();
    auto pred = [type] (auto&& item) { return item.first == type; };
    auto plus = [] (auto&& lhs, auto&& rhs) { return lhs + rhs.second; };

    auto position = std::find_if(begin, end, pred);
    return std::accumulate(begin, position, 0.f, plus) * tile::kTileWidth;
}

} // namespace playfield

bool entityHandleEvent(Playfield::Ptr entity,
                       std::shared_ptr<GameController> controller,
                       const sf::Event& event);

void entityUpdate(Playfield::Ptr entity,
                  std::shared_ptr<GameController> controller,
                  float update_delta_seconds);

} // namespace open_labora

#endif // PLAYFIELD_HPP_
