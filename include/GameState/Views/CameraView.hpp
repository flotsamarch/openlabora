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

#ifndef CAMERAVIEW_HPP_
#define CAMERAVIEW_HPP_

#include "ApplicationState/ApplicationContext.hpp"
#include "IGameWindow.hpp"
#include "Game/Playfield.hpp"
#include "Input/Input.hpp"

namespace open_labora
{

template<class TViewModel>
class CameraView final
{
    IGameWindow::Ptr mGameWindow;
    PtrView<TViewModel> mViewModel;

public:
    CameraView(ApplicationContext::Ptr,
               IGameWindow::Ptr,
               PtrView<TViewModel>);

    bool HandleInput(Input::PtrConst input);
};

template<class TViewModel>
CameraView<TViewModel>
::CameraView(ApplicationContext::Ptr,
             IGameWindow::Ptr game_window,
             PtrView<TViewModel> view_model)
    : mGameWindow{ game_window },
      mViewModel{ view_model }
{
    const auto win_size = static_cast<Vector2f>(game_window->GetWindowSize());
    auto position = Vector2f{ -1 * win_size.x / 2, -1 * win_size.y / 2 };
    auto pf_width = static_cast<float>(playfield::kMaxFieldWidth);
    auto pf_height = static_cast<float>(playfield::kMaxFieldHeight);
    position.x += (pf_width / 2) * tile::kTileWidth;
    position.y += (pf_height / 2) * tile::kTileHeight;

    mGameWindow->SetView(View{ FloatRect{ position, win_size } });
};

template<class TViewModel>
bool CameraView<TViewModel>
::HandleInput(Input::PtrConst input)
{
    if (input->IsMouseMoving()) {
        auto mouse_delta = Vector2f{ input->GetMouseMoveOffset() };

        if (input->IsButtonDown(input::Button::MouseRight) &&
            mViewModel->IsCameraMovementAllowed())
        {
            auto view = mGameWindow->GetView();
            view.move({ -mouse_delta.x, -mouse_delta.y });
            mGameWindow->SetView(view);
        }
        return false;
    }
    return false;
};

} // namespace open_labora

#endif // CAMERAVIEW_HPP_
