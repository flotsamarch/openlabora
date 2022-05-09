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

#ifndef MARKERMANAGER_HPP_
#define MARKERMANAGER_HPP_

#include <vector>
#include <map>
#include <functional>
#include "ExpansionMarker.hpp"
#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

// std::vector wrapper that ensures correct usage of expansion markers
class MarkerManager final
{
    using MarkerType = ExpansionMarker::MarkerType;
    using MarkerVector = std::vector<ExpansionMarker::Ptr>;
    using PlotType = Plot::PlotType;
    using Delegate = std::function<void()>;

    GameController::Ptr mController;
    std::map<PlotType, MarkerVector> mMarkers;
    std::multimap<PlotType, Plot> mPlotsForMarkerCreation;

    void CreateMarker(PlotType, MarkerType, Delegate);

public:
    MarkerManager(GameController::Ptr);
    ~MarkerManager();

    MarkerManager(const MarkerManager&) = delete;
    MarkerManager(MarkerManager&&) = delete;

    MarkerManager& operator=(const MarkerManager&) = delete;
    MarkerManager& operator=(MarkerManager&&) = delete;

     // Updates positions and number of expansion markers
     // @arg on_select - Select() delegate for markers that might get created
    void UpdateMarkers(Delegate on_select);
};

} // namespace OpenLabora

#endif // MARKERMANAGER_HPP_
