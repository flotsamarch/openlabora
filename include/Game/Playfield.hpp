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
#include <SFML/Window/Event.hpp>
#include "ECS/ComponentContainer.hpp"
#include "Components/ImmobileComponent.hpp"
#include "Components/TextureContainerComponent.hpp"
#include "Components/PlayfieldComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Resource/IResourceManager.hpp"

namespace OpenLabora
{

class GameController;

using Playfield = ComponentContainer<ImmobileComponent,
                                     PlayfieldComponent,
                                     TextureContainerComponent,
                                     SpriteComponent>;

namespace playfield
{

Playfield::Ptr create(IResourceManager::Ptr,
                      const sf::Vector2f& initial_position);

Playfield::Ptr create(IResourceManager::Ptr,
                      float initial_x, float initial_y);

} // namespace playfield

bool entityHandleEvent(Playfield::Ptr entity,
                       std::shared_ptr<GameController> controller,
                       const sf::Event& event);

void entityUpdate(Playfield::Ptr entity,
                  float update_delta_seconds,
                  std::shared_ptr<GameController> controller);

} // namespace OpenLabora

#endif // PLAYFIELD_HPP_
