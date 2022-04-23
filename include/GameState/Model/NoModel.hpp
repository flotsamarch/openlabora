#ifndef NOMODEL_HPP_
#define NOMODEL_HPP_

#include "Common.hpp"

namespace OpenLabora
{

struct NoModel final
{
    using Ptr = std::shared_ptr<NoModel>;
    using PtrConst = std::shared_ptr<const NoModel>;

    model::DrawableRangeConst GetDrawableObjects() const noexcept
    { auto it = model::DrawableIterConst{}; return { it, it }; }
};


} // namespace OpenLabora

#endif // NOMODEL_HPP_
