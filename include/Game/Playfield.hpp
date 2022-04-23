#ifndef PLAYFIELD_HPP_
#define PLAYFIELD_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "ECS/ComponentContainer.hpp"
#include "Components/ImmobileComponent.hpp"
#include "Components/TextureContainerComponent.hpp"
#include "Components/PlayfieldComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Misc/PtrView.hpp"

namespace OpenLabora
{

class GameController;

namespace playfield
{

using Playfield = ComponentContainer<ImmobileComponent,
                                     PlayfieldComponent,
                                     TextureContainerComponent,
                                     SpriteComponent>;

std::shared_ptr<Playfield> create(PtrView<GameController>,
                                  const sf::Vector2f& initial_position);

std::shared_ptr<Playfield> create(PtrView<GameController>,
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
