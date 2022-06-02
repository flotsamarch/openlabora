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

#ifndef EXPANSIONMARKER_HPP_
#define EXPANSIONMARKER_HPP_

#include <SFML/Window/Event.hpp>
#include "Components/ExpansionMarkerComponent.hpp"
#include "Components/PositionComponent.hpp"
#include "Components/SelectableComponent.hpp"
#include "Components/SignalComponent.hpp"
#include "Components/EffectiveInteractionAreaComponent.hpp"
#include "Components/SpriteComponent.hpp"
#include "Game/Playfield.hpp"
#include "Resource/IResourceManager.hpp"

namespace OpenLabora
{

class GameController;

using ExpansionMarker = ComponentContainer<ExpansionMarkerComponent,
                                           PositionComponent,
                                           SelectableComponent,
                                           RectangleInteractionAreaComponent,
                                           SignalComponent,
                                           SpriteComponent>;

namespace marker
{

//------------------- ADD TEXTURE ID FOR EACH MARKER HERE ----------------------

constexpr std::string_view kCoastalMarkerTextureName = "coastal_marker";
constexpr std::string_view kCentralMarkerTextureName = "central_marker";
constexpr std::string_view kCentralMarkerAltTextureName = "central_marker_alt";
constexpr std::string_view kMountainMarkerTextureName = "mountain_marker";

using TextureIdMapValueType = std::vector<std::string_view>;

static const TextureIdMapValueType kCentralMarkerTextureNames
{ kCentralMarkerTextureName, kCentralMarkerAltTextureName };

static const EnumMap<plot::Type, TextureIdMapValueType> kTextureIdMap
{
    { plot::Type::Coastal, { kCoastalMarkerTextureName } },
    { plot::Type::Central, kCentralMarkerTextureNames },
    { plot::Type::Mountain, { kMountainMarkerTextureName } },
};

ExpansionMarker::Ptr create(Type marker_type,
                            plot::Type plot_type,
                            std::function<void()> on_left_released,
                            IResourceManager::Ptr);

using MarkerPositions = std::pair<sf::Vector2f, sf::Vector2f>;
MarkerPositions GetBoundaryMarkerPositions(plot::Type, Playfield::PtrConst);

static constexpr float kMarkerOverlapFactor = 1.f / 3.f;

bool handleEvent(ExpansionMarker::Ptr,
                 const sf::Vector2f& mouse_world_pos,
                 const sf::Event&);

} // namespace marker


} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
