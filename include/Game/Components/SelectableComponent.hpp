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

#ifndef SELECTABLECOMPONENT_HPP_
#define SELECTABLECOMPONENT_HPP_

#include "Game/Signal.hpp"

namespace OpenLabora
{

namespace signals
{

inline const Signal kOnSelect{};
inline const Signal kOnDeselect{};
inline const Signal kOnEnter{};
inline const Signal kOnLeave{};

} // namespace signal

class SelectableComponent final
{
    bool bIsSelected{ false };
    bool bHasBeenEntered{ false };

public:
    bool IsSelected() const noexcept { return bIsSelected; }

    bool HasBeenEntered() const noexcept { return bHasBeenEntered; }

    void Select() noexcept { bIsSelected = true; }

    void Deselect() noexcept { bIsSelected = false; }

    void Enter() noexcept { bHasBeenEntered = true; }

    void Leave() noexcept { bHasBeenEntered = false; }
};

} // namespace OpenLabora

#endif // SELECTABLECOMPONENT_HPP_
