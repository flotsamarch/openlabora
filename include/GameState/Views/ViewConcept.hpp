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

#ifndef VIEWCONCEPT_HPP_
#define VIEWCONCEPT_HPP_

#include <concepts>
#include "LibTypedefs.hpp"
#include "Misc/PtrView.hpp"

namespace open_labora
{

class Input;

// Ensure class T satisfies the concept of View in MVVM pattern
template<class T>
concept CView = requires(T t, PtrView<const Input> i)
{ { t.HandleInput(i) } -> std::same_as<bool>; };

} // namespace open_labora

#endif // VIEWCONCEPT_HPP_
