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

#ifndef SELECTABLE_ENTITY_HPP_
#define SELECTABLE_ENTITY_HPP_

#include <SFML/Graphics/Shape.hpp>
#include "Selectable.hpp"
#include "Entity.hpp"
#include "GUI/ClickableArea.hpp"

namespace OpenLabora
{

template<class TShape, SFCombined U>
requires std::is_base_of<sf::Shape, TShape>::value
class SelectableEntity : public Entity<U>, public Selectable
{
protected:
    ClickableArea<TShape> mClickableArea;

public:
    virtual ~SelectableEntity() noexcept {};

    void SetClickableArea(const TShape& area) { mClickableArea = area; }

    void SetSelectDelegate(std::function<void()> delegate)
    { mSelectDelegate = delegate; }

    void SetDeselectDelegate(std::function<void()> delegate)
    { mDeselectDelegate = delegate; }

    void SetOnHoverDelegate(std::function<void()> delegate)
    { mHoverDelegate = delegate; }

    void SetOnOutDelegate(std::function<void()> delegate)
    { mOutDelegate = delegate; }
};

} // namespace OpenLabora

#endif // SELECTABLE_ENTITY_HPP_
