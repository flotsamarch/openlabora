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
#include "Signal.hpp"

namespace OpenLabora
{

using ExpansionMarker = ComponentContainer<ExpansionMarkerComponent,
                                           PositionComponent,
                                           SelectableComponent,
                                           RectangleInteractionAreaComponent,
                                           SignalComponent,
                                           SpriteComponent>;

namespace marker
{

void setPosition(ExpansionMarker&, const sf::Vector2f&);

void setInteractiveRect(ExpansionMarker&,
                        const sf::Vector2f& offset,
                        const sf::Vector2f& size);

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
                            IResourceManager::Ptr);

using MarkerPositions = std::pair<sf::Vector2f, sf::Vector2f>;
MarkerPositions GetBoundaryMarkerPositions(plot::Type, Playfield::PtrConst);

static constexpr float kMarkerOverlapFactor = 1.f / 3.f;

} // namespace marker

bool entityHandleEvent(ExpansionMarker::Ptr,
                       std::shared_ptr<GameController>,
                       const sf::Event&);

void entityUpdate(ExpansionMarker::Ptr,
                  std::shared_ptr<GameController>,
                  float update_delta_seconds);

} // namespace OpenLabora

#endif // EXPANSIONMARKER_HPP_
