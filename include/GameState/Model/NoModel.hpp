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

#ifndef NOMODEL_HPP_
#define NOMODEL_HPP_

#include "Common.hpp"

namespace open_labora
{

struct NoModel final
{
    using Ptr = std::shared_ptr<NoModel>;
    using PtrConst = std::shared_ptr<const NoModel>;

    model::DrawableRangeConst GetDrawableObjects() const noexcept
    { auto it = model::DrawableIterConst{}; return { it, it }; }
};


} // namespace open_labora

#endif // NOMODEL_HPP_
