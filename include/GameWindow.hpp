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

#include <TGUI/Widget.hpp>
#include <SFML/Graphics/View.hpp>
#include "Misc/PtrView.hpp"

namespace OpenLabora
{

// Interface and wrapper for window methods needed during gameplay
// @tparam TGui - A GUI library class
// @tparam TWindow - Render window class
template<class TGui, class TWindow>
class GameWindow final
{
    PtrView<TWindow> mWindow;
    PtrView<TGui> mGui;

public:
    GameWindow(PtrView<TGui> gui, PtrView<TWindow> window)
        : mWindow{ window }, mGui{ gui } {};

    // Set View - ingame region which is drawn and its position on the screen
    void SetView(const sf::View& view) { mWindow->setView(view); }

    decltype(auto) GetView() const { return mWindow->getView(); }

    auto GetSize() { return mWindow->getSize(); } const

    auto MapScreenToWorldCoords(const sf::Vector2i& point) const
    { return mWindow->mapPixelToCoords(point); }

    auto MapWorldToScreenCoords(const sf::Vector2f& coord) const
    { return mWindow->mapCoordsToPixel(coord); }

    void AddWidget(const tgui::Widget::Ptr& widget,
                   const tgui::String& name="") const
    { mGui->add(widget, name); }
};

} // namespace OpenLabora

#endif // GAMEWINDOW_HPP_
