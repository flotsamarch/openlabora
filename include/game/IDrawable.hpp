#ifndef IDRAWABLE_HPP_
#define IDRAWABLE_HPP_

#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>

namespace OpenLabora
{

class IDrawable
{
public:
    using Ptr = std::weak_ptr<IDrawable>;
    using Iter = std::vector<Ptr>::iterator;

    virtual const sf::Drawable& GetDrawableObject() const noexcept = 0;

    virtual bool IsUnderPoint(const sf::Vector2f& point) const = 0;

    virtual ~IDrawable() {};
};

} // namespace OpenLabora

#endif // IDRAWABLE_HPP_
