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

#ifndef ESCAPEMENUVIEWMODEL_HPP_
#define ESCAPEMENUVIEWMODEL_HPP_

#include <functional>

namespace open_labora
{

template<class TModel>
class EscapeMenuViewModel final
{
    using LockCameraMovementCallback = std::function<void()>;
    using UnlockCameraMovementCallback = std::function<void()>;

    bool bMenuOpen{ false };
    LockCameraMovementCallback mLockCameraMovementCallback;
    UnlockCameraMovementCallback mUnlockCameraMovementCallback;

public:
    EscapeMenuViewModel(PtrView<TModel>) {};

    bool IsOpen() const noexcept
    { return bMenuOpen; }

    void SetOpen(bool open = true)
    {
        if(!bMenuOpen && open) {
            mLockCameraMovementCallback();
        } else if (bMenuOpen && !open) {
            mUnlockCameraMovementCallback();
        }
        bMenuOpen = open;
    }

    void SetLockCameraMovementCallback(LockCameraMovementCallback callback)
    { mLockCameraMovementCallback = callback; }

    void SetUnlockCameraMovementCallback(UnlockCameraMovementCallback callback)
    { mUnlockCameraMovementCallback = callback; }
};

} // namespace open_labora

#endif // ESCAPEMENUVIEWMODEL_HPP_
