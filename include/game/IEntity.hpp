#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Drawable.hpp"

class IEntity
{
public:
    virtual ~IEntity() noexcept = 0;
};

inline IEntity::~IEntity() noexcept {};

#endif // IENTITY_HPP_
