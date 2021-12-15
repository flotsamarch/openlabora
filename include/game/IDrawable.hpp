#ifndef IGAMEOBJECT_HPP_
#define IGAMEOBJECT_HPP_

#include <memory>
#include "SFML/Graphics/Sprite.hpp"

class IDrawable
{
public:
    using Ptr = std::shared_ptr<IDrawable>;
    using Iter = std::vector<Ptr>::iterator;

    virtual ~IDrawable() noexcept = 0;

    virtual const sf::Sprite& GetSprite() const noexcept = 0;
};

inline IDrawable::~IDrawable() noexcept {}

#endif // IGAMEOBJECT_HPP_
