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

#ifndef CAMERAVIEWMODEL_HPP_
#define CAMERAVIEWMODEL_HPP_

#include <cassert>
#include <functional>
#include "Misc/PtrView.hpp"
#include "LibTypedefs.hpp"

namespace open_labora
{

template<class TModel>
class CameraViewModel final
{
    PtrView<TModel> mModel;
    int mBlockersCount{ 0 };

public:
    CameraViewModel(PtrView<TModel> model)
        : mModel{ model }
    {
    }

    bool IsCameraMovementAllowed() const
    { return mBlockersCount == 0; }

    void LockCameraMovement()
    { ++mBlockersCount; }

    void UnlockCameraMovement()
    {
        assert(mBlockersCount > 0);
        if (mBlockersCount > 0) {
            --mBlockersCount;
        }
    }
};

} // namespace open_labora

#endif // CAMERAVIEWMODEL_HPP_
