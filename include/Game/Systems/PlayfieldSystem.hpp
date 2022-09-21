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

#ifndef PLAYFIELDSYSTEM_HPP_
#define PLAYFIELDSYSTEM_HPP_

#include <unordered_map>
#include <sstream>
#include "ECS/System.hpp"
#include "ECS/CommonEvents.hpp"
#include "ECS/Registry.hpp"
#include "ECS/MassAssignComponents.hpp"
#include "Game/Systems/Events/CreatePlotEvent.hpp"

namespace open_labora
{

// Manage the playfield i.e. lot deques of each lot type
class PlayfieldSystem final : public System<PlayfieldSystem,
                                            DrawEvent,
                                            CreatePlotEvent>
{
    using LotDequeContainer = std::unordered_map<lot::Type, Entity>;
    IResourceManager::Ptr mResourceMgr;
    LotDequeContainer mLotDeques;

public:
    static constexpr std::string_view kTexturePrefix{ "plot_deque_" };

    PlayfieldSystem(Registry&, IResourceManager::Ptr);

    IResourceManager::Ptr GetResourceManager() const noexcept
    { return mResourceMgr; }

    LotDequeContainer& GetLotDeques() noexcept
    { return mLotDeques; }
};

void systemHandleEvent(PlayfieldSystem&, RegistryRef, const DrawEvent&);

void systemHandleEvent(PlayfieldSystem&, RegistryRef, const CreatePlotEvent&);

} // namespace open_labora

#endif // PLAYFIELDSYSTEM_HPP_
