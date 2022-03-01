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
    using Ptr = std::shared_ptr<IDrawable>;
    using CPtr = std::shared_ptr<const IDrawable>;

    virtual const sf::Drawable& GetDrawableObject() const noexcept = 0;

    virtual sf::FloatRect GetLocalBounds() const = 0;

    virtual sf::FloatRect GetGlobalBounds() const = 0;

    virtual ~IDrawable() {};
};

} // namespace OpenLabora

#endif // IDRAWABLE_HPP_
