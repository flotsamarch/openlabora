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

#ifndef IMMOBILECOMPONENT_HPP_
#define IMMOBILECOMPONENT_HPP_

#include <SFML/System/Vector2.hpp>

namespace open_labora
{

class ImmobileComponent final
{
    sf::Vector2f mPosition;

public:
    ImmobileComponent(const sf::Vector2f& initial_pos)
        : mPosition{ initial_pos } {};

    auto GetPosition() const { return mPosition; }
};

} // namespace open_labora

#endif // IMMOBILECOMPONENT_HPP_
