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

#include "Game/MarkerController.hpp"
#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

namespace marker
{


MarkerController::Ptr createController(sf::Vector2f pf_position)
{
    using MCC = MarkerControllerComponent;
    auto marker_controller = std::make_shared<MarkerController>(MCC{},
                                                                pf_position);

    return marker_controller;
}

} // namespace marker

bool entityHandleEvent(MarkerController::Ptr entity,
                       GameController::Ptr controller,
                       const sf::Event& event)
{
    auto&& component = ecs::getComponent<MarkerControllerComponent>(*entity);
    auto&& mouse_pos = controller->GetModel()->GetWorldMousePosition();
    return component.ForwardEventToMarkers(mouse_pos, event);
}

void entityUpdate(MarkerController::Ptr entity,
                  GameController::Ptr controller,
                  [[maybe_unused]]float update_delta_seconds)
{
    auto&& component = ecs::getComponent<MarkerControllerComponent>(*entity);
    auto markers = component.GetMarkers();

    auto add = [controller] (auto&& marker)
    {
        auto&& sprite_cmpnt = ecs::getComponent<SpriteComponent>(*marker);
        controller->AddDrawableObject(sprite_cmpnt.GetDrawableObject());
    };

    for (auto&& [_, markers_for_plot] : markers) {
        std::for_each(markers_for_plot.begin(), markers_for_plot.end(), add);
    }
    // return component.AddDrawableObjects(controller->GetDrawableBackInserter());
}

} // namespace OpenLabora
