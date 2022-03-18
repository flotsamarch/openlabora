#include "GameState/Controllers/GCDuel.hpp"

namespace OpenLabora
{

GCDuel::GCDuel(PtrView<IApplication<StateIdsVariant>> app,
               IResourceManager::Ptr res_manager,
               Model::Ptr model)
    : GameController(app, res_manager, model, 1) {} // TODO player_count = 2

} // namespace OpenLabora
