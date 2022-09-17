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

#ifndef INTERACTIONAREACOMPONENT_HPP_
#define INTERACTIONAREACOMPONENT_HPP_

#include <LibTypedefs.hpp>

namespace open_labora
{

namespace interaction_area
{

inline bool IsPointInsideShape(const Vector2f& point,
                               const RectangleShape& rect)
{ return rect.getLocalBounds().contains(point); }

} // namespace interaction_area

template<class TShape>
requires std::is_base_of<Shape, TShape>::value
class InteractionAreaComponent final
{
    TShape mShape;             // Shape position is ignored and assumed to be
    Vector2f mShapeOffset; // entity position plus offset

public:
    InteractionAreaComponent() = default;

    InteractionAreaComponent(const TShape& shape,
                                      const Vector2f& offset)
        : mShape{ shape }, mShapeOffset{ offset } {}

    InteractionAreaComponent(TShape&& shape, const Vector2f& offset)
        : mShape{ std::move(shape) }, mShapeOffset{ offset } {}

    // @param point - entity-local coordinates
    bool IsPointInArea(const Vector2f& point) const
    {
        return interaction_area::IsPointInsideShape(point - mShapeOffset,
                                                    mShape);
    }

    void SetOffset(const Vector2f& offset)
    { mShapeOffset = offset; }

    const Vector2f& GetOffset() const
    { return mShapeOffset; }

    void SetShape(TShape shape) { mShape = shape; }
};

using RectangularInteractionAreaComponent =
    InteractionAreaComponent<RectangleShape>;

}// namespace open_labora

#endif // INTERACTIONAREACOMPONENT_HPP_
