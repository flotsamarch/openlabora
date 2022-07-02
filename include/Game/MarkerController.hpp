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

#ifndef MARKERCONTROLLER_HPP_
#define MARKERCONTROLLER_HPP_

#include "ECS/ComponentContainer.hpp"
#include "Components/MarkerControllerComponent.hpp"
#include "Components/ImmobileComponent.hpp"
#include "Components/TextureContainerComponent.hpp"
#include "Components/SpriteComponent.hpp"

namespace OpenLabora
{

class GameController;

using MarkerController = ComponentContainer<MarkerControllerComponent,
                                            ImmobileComponent>;

namespace marker
{

MarkerController::Ptr createController(sf::Vector2f pf_position);

} // namespace marker

bool entityHandleEvent(MarkerController::Ptr,
                       std::shared_ptr<GameController>,
                       const sf::Event&);

void entityUpdate(MarkerController::Ptr,
                  std::shared_ptr<GameController>,
                  float update_delta_seconds);

} // namespace OpenLabora

#endif // MARKERCONTROLLER_HPP_
