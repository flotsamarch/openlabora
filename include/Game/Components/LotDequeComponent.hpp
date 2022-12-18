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

#ifndef LOTDEQUECOMPONENT_HPP_
#define LOTDEQUECOMPONENT_HPP_

#include <deque>
#include "Game/Lot.hpp"

namespace open_labora
{

class LotDequeComponent final
{
    using Type = lot::Type;
    using SubtypeId = lot::SubtypeId;
    using LotContainer = std::deque<SubtypeId>;

    Type mLotType;
    LotContainer mLots;

public:
    LotDequeComponent(Type lot_type)
        : mLotType{ lot_type } {}

    void AddLotToTop(SubtypeId subtype)
    { mLots.push_front(subtype); }

    void AddLotToBottom(SubtypeId subtype)
    { mLots.push_back(subtype); }

    int GetLotsCount() const noexcept
    { return static_cast<int>(mLots.size()); }

    Type GetLotType() const noexcept
    { return mLotType; }

    SubtypeId operator[](int index) const
    { return mLots[index]; }

    LotContainer::const_iterator begin() const noexcept
    { return mLots.begin(); }

    LotContainer::const_iterator end() const noexcept
    { return mLots.end(); }
};

} // namespace open_labora

#endif // LOTDEQUECOMPONENT_HPP_
