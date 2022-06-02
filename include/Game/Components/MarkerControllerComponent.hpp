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

#ifndef MARKERCONTROLLERCOMPONENT_HPP_
#define MARKERCONTROLLERCOMPONENT_HPP_

#include <iterator>
#include <concepts>
#include "Game/Plot.hpp"
#include "Game/Playfield.hpp"
#include "Game/ExpansionMarker.hpp"
#include "Misc/PtrView.hpp"
#include "Misc/EnumMap.hpp"

namespace OpenLabora
{

class GameController;

class MarkerControllerComponent final
{
    using Marker = ExpansionMarker;

    // Less memory footprint than vector in this case most of the time.
    // Also I would prefer to just insert new elements right before last element
    // instead of doing weird tricks with keeping persistent elements in the
    // beggining and pushing new ones to the back.
    using MarkerContainer = std::list<Marker::Ptr>;
    using MarkerMap = EnumMap<plot::Type, MarkerContainer>;

    MarkerMap mMarkers;
    Marker::Ptr mSelectedMarker{};

    Marker::Ptr CreateMarker(marker::Type, plot::Type,
                             std::function<void()> on_left_released_delegate,
                             IResourceManager::Ptr);

public:
    void RemoveExcessMarkers(Playfield::PtrConst);

    void CreateMissingMarkers(Playfield::PtrConst,
                              std::function<void()> on_left_released_delegate,
                              IResourceManager::Ptr);

    void TranslateMarkers(Playfield::PtrConst);

    bool ForwardEventToMarkers(const sf::Vector2f& mouse_world_pos,
                               const sf::Event&) const;

    auto GetMarkers() const
    { return RangeWrapper{ mMarkers.cbegin(), mMarkers.cend() }; }

    // @return Shared ptr to selected marker or nullptr if none is selected
    ExpansionMarker::Ptr GetSelecterMarker() const noexcept
    { return mSelectedMarker; }

    void DeselectMarker();
};

} // namespace OpenLabora

#endif // MARKERCONTROLLERCOMPONENT_HPP_
