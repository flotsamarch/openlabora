#ifndef STATEIDS_HPP_
#define STATEIDS_HPP_

#include <variant>

namespace OpenLabora
{

// ------------------------ ADD ALL STATE IDS HERE ------------------------------
struct MainMenuStateId final {};
struct DuelStateId final {};
struct FinalStateId final {};

using StateIdsVariant = std::variant<MainMenuStateId, DuelStateId, FinalStateId>;

} // namespace OpenLabora

#endif // STATEIDS_HPP_
