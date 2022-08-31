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

#ifndef LIBTYPEDEFS_HPP_
#define LIBTYPEDEFS_HPP_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <vector>
#include <memory>
#include "Misc/RangeWrapper.hpp"

namespace open_labora
{

using Drawable = sf::Drawable;
using Sprite = sf::Sprite;

using DrawableContainer = std::vector<std::reference_wrapper<const Drawable>>;
using DrawableIterConst = DrawableContainer::const_iterator;
using DrawableRangeConst = RangeWrapper<DrawableIterConst>;

using View = sf::View;

using Vector2u = sf::Vector2u;
using Vector2f = sf::Vector2f;
using Vector2i = sf::Vector2i;

using Texture = sf::Texture;
using RenderTexture = sf::RenderTexture;
using RenderWindow = sf::RenderWindow;

using VideoMode = sf::VideoMode;
using Color = sf::Color;

using FloatRect = sf::FloatRect;
using IntRect = sf::IntRect;

using RectangleShape = sf::RectangleShape;

constexpr auto kWindowStyle = sf::Style::Fullscreen;

} // namespace open_labora

#endif // LIBTYPEDEFS_HPP_
