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

#ifndef PLOTACQUISITIONVIEW_HPP_
#define PLOTACQUISITIONVIEW_HPP_

#include "ApplicationState/ApplicationContext.hpp"
#include "IGameWindow.hpp"
#include "Input/Input.hpp"
#include "GUI/PlotAcquisitionMenu.hpp"

namespace open_labora
{

namespace plot_acquisition
{

using MenuStateId = plot_acquisition::MenuWindowId;

constexpr EnumMap<lot::Type, MenuWindowId> kLotTypeToWindowStateMap =
{
    { lot::Type::Central, MenuWindowId::ChooseOne },
    { lot::Type::Coastal, MenuWindowId::Confirm },
    { lot::Type::Mountain, MenuWindowId::Confirm },
};

struct CreateWindowParams final
{
    CreateWindowParams(ButtonToPlotTypeIdMap& button_to_type_id_map)
        : button_to_type_id{ button_to_type_id_map } {};

    ButtonToPlotTypeIdMap& button_to_type_id;
    IGameWindow::Ptr game_window;
    PlotAcquisitionMenu::HideVisibleWindowCallback hide_visible_callback;
    plot::AcquireCallback acquire_plot_callback;
    ConfirmationWindow::DeclineAction decline_action;
};

struct CreateWindowResult
{
    MenuWindowId id;
    ConfirmationWindow window;
};

CreateWindowResult createWindowConfirm(CreateWindowParams&);

CreateWindowResult createWindowChooseOne(CreateWindowParams&);

constexpr std::array createWindowFunctions
{
    createWindowChooseOne, createWindowConfirm
};

} // namespace plot_acquisition

template<class TViewModel>
class PlotAcquisitionView final
{
    IGameWindow::Ptr mGameWindow;
    PtrView<TViewModel> mViewModel;
    PlotAcquisitionMenu mMenu{};
    plot_acquisition::ButtonToPlotTypeIdMap mButtonToTypeIdMap;

public:
    PlotAcquisitionView(ApplicationContext::Ptr,
                        IGameWindow::Ptr,
                        PtrView<TViewModel>);

    size_t GetWindowCount() const noexcept { return mButtonToTypeIdMap.size(); }

    const PlotAcquisitionMenu& GetMenu() const noexcept { return mMenu; };

    bool HandleInput(Input::PtrConst input);

    void Update([[maybe_unused]]float update_delta_seconds)
    {
    }
};

template<class TViewModel>
PlotAcquisitionView<TViewModel>
::PlotAcquisitionView(ApplicationContext::Ptr,
                      IGameWindow::Ptr game_window,
                      PtrView<TViewModel> view_model)
    : mGameWindow{ game_window },
      mViewModel{ view_model }
{
    namespace pa = plot_acquisition;

    auto close_menu =
    [&menu = mMenu, view_model]
    {
        view_model->DeselectMarker();
        menu.HideCurrentlyVisible();
    };

    auto acquire_plot =
    [view_model] (plot::AcquirePlotParams& params) -> plot::AcquireReturnType
    {
        view_model->AcquirePlot(params);
    };

    auto hide_visible_window = [&menu = mMenu] { menu.HideCurrentlyVisible(); };

    auto params = pa::CreateWindowParams{ mButtonToTypeIdMap };
    params.game_window = game_window;
    params.acquire_plot_callback = std::move(acquire_plot);
    params.decline_action = std::move(close_menu);
    params.hide_visible_callback = std::move(hide_visible_window);

    auto create_and_add_window =
    [&params, &menu = mMenu] (auto create_window_function)
    {
        auto result = create_window_function(params);
        menu.Emplace(result.id, std::move(result.window));
    };

    std::for_each(pa::createWindowFunctions.begin(),
                  pa::createWindowFunctions.end(),
                  create_and_add_window);
}

template<class TViewModel>
bool PlotAcquisitionView<TViewModel>::HandleInput(Input::PtrConst input)
{
    namespace pa = plot_acquisition;
    const auto position = input->GetMousePosition();
    const auto world_pos = mGameWindow->MapScreenToWorldCoords(position);

    if (input->HasButtonBeenReleased(input::Button::MouseLeft)) {
        auto is_selected = mViewModel->SelectMarker(world_pos);

        if (is_selected) {
            const auto type = mViewModel->GetSelectedMarkerLotType();
            const auto state = pa::kLotTypeToWindowStateMap.Get(type);
            mMenu.Show(state);
        }

        return is_selected;
    }

    if (input->IsMouseMoving()) {
        mViewModel->HighlightMarker(world_pos);
    }

    return false;
}

} // namespace open_labora

#endif // PLOTACQUISITIONVIEW_HPP_
