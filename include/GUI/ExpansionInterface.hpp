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

#ifndef EXPANSIONINTERFACE_HPP_
#define EXPANSIONINTERFACE_HPP_

#include <functional>
#include "Game/ExpansionMarker.hpp"
#include "GameWindow.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "Resource/IResourceManager.hpp"
#include "GUI/ExpansionWindow.hpp"
#include "Game/MarkerController.hpp"
#include "Misc/EnumMap.hpp"

namespace OpenLabora
{

namespace expansionWindow
{

using WindowStatesVariant = std::variant<StateChooseOne, StateConfirm>;
inline const EnumMap<plot::Type, WindowStatesVariant> kWindowStatesMap
{
    { plot::Type::Coastal, WindowStatesVariant{ StateConfirm{} } },
    { plot::Type::Central, WindowStatesVariant{ StateChooseOne{} } },
    { plot::Type::Mountain, WindowStatesVariant{ StateConfirm{} } }
};

} // namespace expansionWindow

// Class responsible for interactive elements that allow expansion of playfield
class ExpansionInterface final
{
    using MarkerType = marker::Type;
    using PlotType = plot::Type;
    using Delegate = std::function<void()>;

    ExpansionWindow mExpansionWindow;
    MarkerController::Ptr mMarkerController;

    void CreateMarker(PlotType, MarkerType, Delegate);

public:
    template<class TGui, class TWindow>
    ExpansionInterface(GameWindow<TGui, TWindow>, GameController::Ptr);
};

template<class TGui, class TWindow>
ExpansionInterface::ExpansionInterface(GameWindow<TGui, TWindow> game_window,
                                       GameController::Ptr controller)
    : mExpansionWindow(game_window)

{
    auto&& playfield = controller->GetActivePlayerPlayfield();
    auto&& immobile_cmpnt = ecs::getComponent<ImmobileComponent>(*playfield);

    mMarkerController = marker::createController(immobile_cmpnt.GetPosition());
    controller->AddMarkerControllerToModel(mMarkerController);
    auto&& resource_mgr = controller->GetResourceManager();

    auto close_confirm_window =
    [&window = mExpansionWindow, controller = mMarkerController]
    {
        using MCC = MarkerControllerComponent;
        auto&& component = ecs::getComponent<MCC>(*controller);
        component.DeselectMarker();
        window.Show(false);
    };

    auto get_selected_marker = [controller = mMarkerController]
    {
        using MCC = MarkerControllerComponent;
        auto&& component = ecs::getComponent<MCC>(*controller);
        return component.GetSelecterMarker();

    };

    auto show_window =
    [&window = mExpansionWindow, get_selected_marker]
    {
        auto marker = get_selected_marker();
        if (marker == nullptr) {
            return;
        }

        using EMC = ExpansionMarkerComponent;
        auto&& marker_cmpnt = ecs::getComponent<EMC>(*marker);
        auto type = marker_cmpnt.GetPlotType();
        auto state = expansionWindow::kWindowStatesMap.Get(type);
        auto set_state = [&window] (auto&& state) { window.SetState(state); };

        std::visit(set_state, state);
        window.Show(true);
    };

    auto get_params = [get_selected_marker, &window = mExpansionWindow]
    {
        using EMC = ExpansionMarkerComponent;
        auto&& marker = get_selected_marker();
        auto&& marker_cmpnt = ecs::getComponent<EMC>(*marker);
        assert(marker != nullptr);
        auto&& plots = marker_cmpnt.GetPlots();
        const auto add_to_top = marker_cmpnt.GetType() == marker::Type::Upper;
        const auto alt_required = window.GetToggleValue() == 2;
        return playfield::PlotCreationParams{ plots, add_to_top, alt_required };
    };

    auto add_new_plot = controller->MakePlotCreationDelegate(get_params);

    auto update_markers =
    [playfield, show_window, resource_mgr, marker_controller = mMarkerController]
    {
        using MCC = MarkerControllerComponent;
        auto&& controller_component = ecs::getComponent<MCC>(*marker_controller);

        controller_component.RemoveExcessMarkers(playfield);
        controller_component.CreateMissingMarkers(playfield,
                                                  show_window,
                                                  resource_mgr);
        controller_component.TranslateMarkers(playfield);
    };
    update_markers();

    auto&& confirm_btn = mExpansionWindow.GetConfirmButton();
    auto&& decline_btn = mExpansionWindow.GetDeclineButton();
    auto&& expansion_win = mExpansionWindow.GetWindow();

    // Order is important
    confirm_btn->onPress(add_new_plot);
    confirm_btn->onPress(close_confirm_window);
    confirm_btn->onPress(update_markers);

    decline_btn->onPress(close_confirm_window);
    expansion_win->onClose(close_confirm_window);
}

} // namespace OpenLabora

#endif // EXPANSIONINTERFACE_HPP_
