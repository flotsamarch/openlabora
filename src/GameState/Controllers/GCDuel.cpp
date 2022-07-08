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

#include "GameState/Controllers/GCDuel.hpp"

namespace open_labora
{

GCDuel::GCDuel(PtrView<IApplication<StateIdsVariant>> app,
               IResourceManager::Ptr resource_mgr,
               Model::Ptr model)
    : GameController(app, resource_mgr, model, 1) {} // TODO player_count = 2

} // namespace open_labora
