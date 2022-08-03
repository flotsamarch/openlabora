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

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include "ApplicationState/ApplicationContext.hpp"
#include "IGameWindow.hpp"
#include "Input/Input.hpp"

namespace open_labora
{

struct IResourceManager;

class MainMenu final
{
    ApplicationContext::Ptr mApp;
    IGameWindow::Ptr mWindow;
    Input::Ptr mInput;

public:
    ~MainMenu()
    { mWindow->RemoveAllWidgets(); }

    MainMenu(const MainMenu&) = delete;
    MainMenu(MainMenu&&) = delete;
    MainMenu& operator=(const MainMenu&) = delete;
    MainMenu& operator=(MainMenu&&) = delete;

    MainMenu(ApplicationContext::Ptr,
             IGameWindow::Ptr,
             std::shared_ptr<IResourceManager>);

    ApplicationContext::Ptr GetApp() noexcept
    { return mApp; }

    Input::Ptr GetInput() noexcept
    { return mInput; }
};

void stateUpdate(MainMenu&, float update_delta_seconds);

void stateHandleInput(MainMenu&, Input::PtrConst);

DrawableRangeConst stateGetDrawableObjects(MainMenu&);

bool stateGetFlagIsFinal(const MainMenu&) noexcept;

} // namespace open_labora

#endif // MAINMENU_HPP_
