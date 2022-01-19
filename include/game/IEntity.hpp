#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/Drawable.hpp"

namespace OpenLabora
{

class IEntity
{
public:
    virtual ~IEntity() = 0;
};

inline IEntity::~IEntity() {};

} // namespace OpenLabora

#endif // IENTITY_HPP_
