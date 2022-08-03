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

#ifndef MAINMENUFWD_HPP_
#define MAINMENUFWD_HPP_

#include <memory>
#include "Misc/PtrView.hpp"

namespace open_labora
{

struct IResourceManager;
struct IGameWindow;
class ApplicationContext;

namespace state
{

struct MainMenu{};

void changeState(MainMenu,
                 PtrView<ApplicationContext>,
                 std::shared_ptr<IGameWindow>,
                 std::shared_ptr<IResourceManager>);

} // namespace state

} // namespace open_labora

#endif // MAINMENUFWD_HPP_
