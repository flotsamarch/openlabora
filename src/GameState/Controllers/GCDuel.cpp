#include "GameState/Controllers/GCDuel.hpp"

namespace OpenLabora
{

GCDuel::GCDuel(std::shared_ptr<AppStateManager> state,
               std::shared_ptr<Model> model)
    : GameController(state, model, 1) {} // TODO player_count = 2

} // namespace OpenLabora
