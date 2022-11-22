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
#include <TGUI/Widgets/ChildWindow.hpp>
#include <TGUI/Widgets/Button.hpp>
#include <TGUI/Widgets/RadioButton.hpp>
#include <TGUI/Widgets/RadioButtonGroup.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Panel.hpp>

namespace open_labora
{

using Gui = tgui::GuiSFML;

using Widget = tgui::Widget;
using Button = tgui::Button;
using RadioButton = tgui::RadioButton;
using Label = tgui::Label;
using Panel = tgui::Panel;
using ChildWindow = tgui::ChildWindow;

using GuiString = tgui::String;

using Group = tgui::Group;
using VBox = tgui::VerticalLayout;
using HBox = tgui::HorizontalLayout;
using RadioGroup = tgui::RadioButtonGroup;

using TitleButtonStyle = tgui::ChildWindow::TitleButton;

using tgui::bindBottom;
using tgui::bindTop;
using tgui::bindLeft;
using tgui::bindRight;

} // namespace open_labora

#endif // GUITYPEDEFS_HPP_
