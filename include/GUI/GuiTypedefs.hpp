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

#ifndef GUITYPEDEFS_HPP_
#define GUITYPEDEFS_HPP_

#include <TGUI/Backends/SFML.hpp>
#include <TGUI/Widget.hpp>
#include <TGUI/Widgets/VerticalLayout.hpp>
#include <TGUI/Widgets/HorizontalLayout.hpp>
#include <TGUI/Widgets/Button.hpp>

namespace open_labora
{

using Gui = tgui::GuiSFML;

using Widget = tgui::Widget;
using GuiString = tgui::String;
using Button = tgui::Button;
using VBox = tgui::VerticalLayout;
using HBox = tgui::HorizontalLayout;

} // namespace open_labora

#endif // GUITYPEDEFS_HPP_
