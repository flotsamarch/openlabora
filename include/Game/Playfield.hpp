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

namespace playfield
{

using Playfield = ComponentContainer<ImmobileComponent,
                                     PlayfieldComponent,
                                     TextureContainerComponent,
                                     SpriteComponent>;

std::shared_ptr<Playfield> create(IResourceManager::Ptr,
                                  const sf::Vector2f& initial_position);

std::shared_ptr<Playfield> create(IResourceManager::Ptr,
                                  float initial_x, float initial_y);

} // namespace playfield

bool entityHandleEvent(std::shared_ptr<playfield::Playfield> entity,
                       std::shared_ptr<GameController> controller,
                       const sf::Event& event);

void entityUpdate(std::shared_ptr<playfield::Playfield> entity,
                  float update_delta_seconds,
                  std::shared_ptr<GameController> controller);

} // namespace OpenLabora

#endif // PLAYFIELD_HPP_
