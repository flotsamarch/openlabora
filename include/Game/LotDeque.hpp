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

#ifndef LOTDEQUE_HPP_
#define LOTDEQUE_HPP_

#include "ECS/Registry.hpp"
#include "Components/LotDequeComponent.hpp"

namespace open_labora
{

namespace lot_deque
{

Entity create(RegistryRef, lot::Type, const Vector2f& position);

struct LotsInfo
{
    Vector2f position;
    int count = 0;
};

using LotsInfoMap = std::unordered_map<lot::Type, LotsInfo>;

LotsInfoMap createLotsInfo(RegistryRef);

} // namespace lot_deque

} // namespace open_labora

#endif // LOTDEQUE_HPP_
