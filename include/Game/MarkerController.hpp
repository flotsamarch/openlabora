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

#include <iterator>
#include <concepts>
#include "Game/Plot.hpp"
#include "Game/Playfield.hpp"
#include "Game/ExpansionMarker.hpp"
#include "Misc/EnumMap.hpp"

namespace open_labora
{

class MarkerController final
{
    using Marker = ExpansionMarker;
    using OnLeftReleaseDelegate = std::function<void()>;
    using MarkerAndId = std::pair<uid::Uid, Marker::Ptr>;

    // Less memory footprint than vector in this case most of the time.
    // Also I would prefer to just insert new elements right before last element
    // instead of doing weird tricks with keeping persistent elements in the
    // beginning and pushing new ones to the back.
    using MarkerContainer = std::list<MarkerAndId>;
    using MarkerMap = EnumMap<plot::Type, MarkerContainer>;

    MarkerMap mMarkers;
    Marker::Ptr mSelectedMarker{};

public:
    using MarkerRegistrar = std::function<uid::Uid(Marker::Ptr)>;
    using MarkerBulkDeleter = std::function<void(std::span<uid::Uid>)>;

private:
    MarkerAndId CreateMarker(MarkerRegistrar,
                             marker::Type,
                             plot::Type,
                             OnLeftReleaseDelegate,
                             IResourceManager::Ptr);

public:
    using Ptr = std::shared_ptr<MarkerController>;

    void RemoveExcessMarkers(Playfield::PtrConst,
                             MarkerBulkDeleter bulk_deleter);

    void CreateMissingMarkers(Playfield::PtrConst,
                              MarkerRegistrar,
                              OnLeftReleaseDelegate,
                              IResourceManager::Ptr);

    void TranslateMarkers(Playfield::PtrConst);

    auto GetMarkers() const
    { return RangeWrapper{ mMarkers.cbegin(), mMarkers.cend() }; }

    // @return Shared ptr to selected marker or nullptr if none is selected
    Marker::Ptr GetSelecterMarker() const noexcept
    { return mSelectedMarker; }

    void DeselectMarker();
};

} // namespace open_labora

#endif // MARKERCONTROLLER_HPP_
