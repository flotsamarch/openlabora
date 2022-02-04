#ifndef IENTITY_HPP_
#define IENTITY_HPP_

#include <memory>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>

namespace OpenLabora
{

class IEntity
{
public:
    using Ptr = std::shared_ptr<IEntity>;
    using CPtr = std::shared_ptr<const IEntity>;

    virtual ~IEntity() = 0;
};

inline IEntity::~IEntity() {};

} // namespace OpenLabora

#endif // IENTITY_HPP_
