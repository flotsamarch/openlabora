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

#ifndef COMMON_HPP_
#define COMMON_HPP_

#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include "Misc/RangeWrapper.hpp"

namespace OpenLabora::model
{

using DrawableCPtr = std::unique_ptr<sf::Drawable>;
using DrawableContainer = std::vector<DrawableCPtr>;
using DrawableIterConst = DrawableContainer::const_iterator;
using DrawableRangeConst = RangeWrapper<DrawableIterConst>;

template<class T>
concept Drawable = std::derived_from<std::remove_cvref_t<T>, sf::Drawable>;

} // namespace OpenLabora::model

#endif // COMMON_HPP_
