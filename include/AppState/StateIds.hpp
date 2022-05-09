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
