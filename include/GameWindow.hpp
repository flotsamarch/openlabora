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

#ifndef GAMEWINDOW_HPP_
#define GAMEWINDOW_HPP_

#include "IGameWindow.hpp"
#include "Misc/PtrView.hpp"
#include "LibTypedefs.hpp"
#include "GUI/GuiTypedefs.hpp"

namespace open_labora
{

class GameWindow final : public IGameWindow
{
    PtrView<RenderWindow> mWindow;
    PtrView<Gui> mGui;

public:
    GameWindow(PtrView<Gui> gui, PtrView<RenderWindow> window)
        : mWindow{ window }, mGui{ gui } {};

    void SetView(const View& view) override
    { mWindow->setView(view); }

    const View& GetView() const override
    { return mWindow->getView(); }

    Vector2u GetWindowSize() const override
    { return mWindow->getSize(); }

    Vector2f MapScreenToWorldCoords(const Vector2i& point) const override
    { return mWindow->mapPixelToCoords(point); }

    Vector2i MapWorldToScreenCoords(const Vector2f& coord) const override
    { return mWindow->mapCoordsToPixel(coord); }

    void AddWidget(Widget::Ptr widget, const GuiString& name) const override
    { mGui->add(widget, name); }

    void AddWidget(Widget::Ptr widget) const override
    { AddWidget(widget, ""); }

    void RemoveAllWidgets() override
    { mGui->removeAllWidgets(); }
};

} // namespace open_labora

#endif // GAMEWINDOW_HPP_
