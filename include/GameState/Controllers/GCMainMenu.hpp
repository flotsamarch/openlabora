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

#ifndef GCMAINMENU_HPP_
#define GCMAINMENU_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Model/NoModel.hpp"

namespace OpenLabora
{

// Game controller for Main Menu state
class GCMainMenu final
{
public:
    using Ptr = std::shared_ptr<GCMainMenu>;

    PtrView<IApplication<StateIdsVariant>> mApp;
    NoModel::Ptr mModel;
    IResourceManager::Ptr mResourceMgr;

    GCMainMenu(PtrView<IApplication<StateIdsVariant>>,
               IResourceManager::Ptr,
               NoModel::Ptr);

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);
};

} // namespace OpenLabora

#endif // GCMAINMENU_HPP_
