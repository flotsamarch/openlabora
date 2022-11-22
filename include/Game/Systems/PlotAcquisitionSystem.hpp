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

#ifndef PLOTACQUISITIONSYSTEM_HPP_
#define PLOTACQUISITIONSYSTEM_HPP_

#include "ECS/System.hpp"
#include "ECS/Registry.hpp"
#include "Events/UpdateMarkersEvent.hpp"
#include "Resource/IResourceManager.hpp"
#include "Game/LotDeque.hpp"

namespace open_labora
{

// System responsible for positioning and creation of plots.
// Must be assigned to feature before PlayfieldSystem
class PlotAcquisitionSystem final : public System<PlotAcquisitionSystem,
                                                  UpdateMarkersEvent>
{
public:
    using MarkerContainer = std::vector<Entity>;
    using MarkerMap = EnumMap<lot::Type, MarkerContainer>;

private:
    IResourceManager::Ptr mResourceMgr;
    MarkerMap mMarkers{};

public:
    PlotAcquisitionSystem(Registry&, IResourceManager::Ptr);

    IResourceManager::Ptr GetResourceManager() const noexcept
    { return mResourceMgr; }

    // Does not leak access since system is type erased inside "feature" class
    MarkerMap& GetMarkerMap() noexcept { return mMarkers; }
};

void systemHandleEvent(PlotAcquisitionSystem&,
                       RegistryRef,
                       const UpdateMarkersEvent&);

namespace plot_acquisition
{

void removeExcessMarkers(PlotAcquisitionSystem::MarkerContainer&,
                         lot::Type,
                         const lot_deque::LotsInfoMap&,
                         RegistryRef);

void createMissingMarkers(PlotAcquisitionSystem::MarkerContainer&,
                          lot::Type,
                          const lot_deque::LotsInfoMap&,
                          RegistryRef registry,
                          IResourceManager::Ptr resource_mgr);

void updateMarkerPositions(PlotAcquisitionSystem::MarkerContainer&,
                           lot::Type,
                           const lot_deque::LotsInfoMap&);

void updateMarkerInteractionAreas(PlotAcquisitionSystem::MarkerContainer&);

} // namespace plot_acquisition

} // namespace open_labora

#endif // PLOTACQUISITIONSYSTEM_HPP_
