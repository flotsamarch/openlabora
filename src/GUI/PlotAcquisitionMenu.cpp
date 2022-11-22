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

#include "GUI/PlotAcquisitionMenu.hpp"

namespace open_labora
{

void PlotAcquisitionMenu::HideCurrentlyVisible()
{
    auto it = mWindows.find(mCurrentlyVisible);

    if (it != mWindows.end()) {
        it->second.Show(false);
    }
}

void PlotAcquisitionMenu::Show(MenuWindowId id, bool show)
{
    assert(id >= MenuWindowId::Begin);
    assert(id < MenuWindowId::End);

    auto it = mWindows.find(id);

    if (it == mWindows.end()) {
        return;
    }

    if (show) {
        HideCurrentlyVisible();
    }

    mCurrentlyVisible = id;
    it->second.Show(show);
};

bool PlotAcquisitionMenu::IsVisible(MenuWindowId state) const
{
    auto it = mWindows.find(state);
    return it != mWindows.end() && it->second.IsVisible();
}

} // namespace open_labora
