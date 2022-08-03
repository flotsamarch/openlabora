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

#ifndef IGAMEWINDOW_HPP_
#define IGAMEWINDOW_HPP_

#include "LibTypedefs.hpp"
#include "GUI/GuiTypedefs.hpp"

namespace open_labora
{

/**
 * Interface that provides access only to gameplay-specific methods of
 * RenderWindow and Gui
 */
struct IGameWindow
{
    using Ptr = std::shared_ptr<IGameWindow>;

    virtual ~IGameWindow() = default;

    // Set View - a region which is drawn on screen
    virtual void SetView(const View&) = 0;

    virtual const View& GetView() const = 0;

    virtual Vector2u GetWindowSize() const = 0;

    virtual Vector2f MapScreenToWorldCoords(const Vector2i& point) const = 0;

    virtual Vector2i MapWorldToScreenCoords(const Vector2f& coord) const = 0;

    // Add widget to enable its rendering
    virtual void AddWidget(Widget::Ptr, const GuiString& name) const = 0;
    virtual void AddWidget(Widget::Ptr) const = 0;

    virtual void RemoveAllWidgets() = 0;
};

} // namespace open_labora

#endif // IGAMEWINDOW_HPP_
