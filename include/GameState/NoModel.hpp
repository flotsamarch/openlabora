#ifndef NOMODEL_HPP_
#define NOMODEL_HPP_

#include <memory>
#include <span>
#include "Game/IDrawable.hpp"

namespace OpenLabora
{

struct NoModel
{
    using Ptr = std::shared_ptr<NoModel>;
    using CPtr = std::shared_ptr<const NoModel>;

    using CDrawableSpan = std::span<const std::shared_ptr<const IDrawable>>;
    CDrawableSpan GetDrawableEntities() const noexcept { return {}; }
};


} // namespace OpenLabora

#endif // NOMODEL_HPP_
