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

#ifndef EFFECTIVEINTERACTIONAREA_HPP_
#define EFFECTIVEINTERACTIONAREA_HPP_

#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace open_labora
{

namespace interaction
{

inline bool IsPointInsideShape(const sf::Vector2f& point,
                               const sf::RectangleShape& rect)
{ return rect.getLocalBounds().contains(point); }

} // namespace interaction

template<class TShape>
requires std::is_base_of<sf::Shape, TShape>::value
class EffectiveInteractionAreaComponent final
{
    TShape mShape;             // Shape position is ignored and assumed to be
    sf::Vector2f mShapeOffset; // entity position plus offset

public:
    EffectiveInteractionAreaComponent() = default;

    EffectiveInteractionAreaComponent(const TShape& shape,
                                      const sf::Vector2f& offset)
        : mShape{ shape }, mShapeOffset{ offset } {}

    EffectiveInteractionAreaComponent(TShape&& shape, const sf::Vector2f& offset)
        : mShape{ std::move(shape) }, mShapeOffset{ offset } {}

    // @param point - entity-local coordinates
    bool IsPointInArea(const sf::Vector2f& point)
    { return interaction::IsPointInsideShape(point - mShapeOffset, mShape); }

    void SetOffset(const sf::Vector2f& offset)
    { mShapeOffset = offset; }

    const sf::Vector2f& GetOffset() const
    { return mShapeOffset; }

    void SetShape(TShape shape) { mShape = shape; }
};

using RectangleInteractionAreaComponent =
    EffectiveInteractionAreaComponent<sf::RectangleShape>;

}// namespace open_labora

#endif // EFFECTIVEINTERACTIONAREA_HPP_
