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

#ifndef PLOTACQUISITIONMENU_HPP_
#define PLOTACQUISITIONMENU_HPP_

#include "GuiTypedefs.hpp"
#include "Misc/CommonTypedefs.hpp"
#include "ConfirmationWindow.hpp"
#include "Game/Plot.hpp"

namespace open_labora
{

namespace plot_acquisition
{

enum class MenuWindowId
{
    Begin, ChooseOne = Begin, Confirm, End
};

using ButtonToPlotTypeIdMap = std::unordered_map<RadioButton::Ptr, plot::TypeId>;

} // namespace plot_acquisition

// Class that handles showing one correct plot purchase confirmation window
class PlotAcquisitionMenu final
{
    using MenuWindowId = plot_acquisition::MenuWindowId;

public:
    using WindowsContainer = std::unordered_map<MenuWindowId,
                                                ConfirmationWindow>;

    using HideVisibleWindowCallback = std::function<void()>;

private:
    WindowsContainer mWindows{};
    MenuWindowId mCurrentlyVisible{};

public:
    void HideCurrentlyVisible();

    void Show(MenuWindowId, bool show = true);

    bool IsVisible(MenuWindowId) const;

    template<class... Args>
    void Emplace(MenuWindowId, Args...);
};

template<class... Args>
void PlotAcquisitionMenu::Emplace(MenuWindowId id, Args... args)
{
    auto result = mWindows.try_emplace(id, std::forward<Args>(args)...);

    if (!result.second) {
        return;
    }

    result.first->second.Show(false);
}

} // namespace open_labora

#endif // PLOTACQUISITIONMENU_HPP_
