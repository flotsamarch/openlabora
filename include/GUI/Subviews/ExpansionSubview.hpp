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

#ifndef EXPANSIONSUBVIEW_HPP_
#define EXPANSIONSUBVIEW_HPP_

#include <functional>
#include "Game/ExpansionMarker.hpp"
#include "GameWindow.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "Resource/IResourceManager.hpp"
#include "GUI/ExpansionWindow.hpp"
#include "Game/MarkerController.hpp"
#include "Misc/EnumMap.hpp"
#include "SubviewInitializer.hpp"

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

// Subview that handles user interface for playfield expansion
class ExpansionSubview final
{
    using MarkerType = marker::Type;
    using PlotType = plot::Type;
    using Delegate = std::function<void()>;

    template<class TGui, class TWindow, class TGameController>
    using Initializer = SubviewInitializer<TGui, TWindow, TGameController>;

    ExpansionWindow mExpansionWindow;
    MarkerController::Ptr mMarkerController;

    void CreateMarker(PlotType, MarkerType, Delegate);

public:
    template<class TGui, class TWindow, class TGameController>
    ExpansionSubview(Initializer<TGui, TWindow, TGameController>);
};

template<class TGui, class TWindow, class TGameController>
ExpansionSubview
::ExpansionSubview(Initializer<TGui, TWindow, TGameController> initializer)
    : mExpansionWindow{ initializer.game_window },
      mMarkerController{ std::make_shared<MarkerController>() }
{
    auto controller = initializer.game_controller;
    auto&& playfield = controller->GetActivePlayerPlayfield();

    auto&& resource_mgr = controller->GetResourceManager();

    auto close_confirm_window =
    [&window = mExpansionWindow, marker_controller = mMarkerController]
    {
        marker_controller->DeselectMarker();
        window.Show(false);
    };

    auto get_selected_marker = [marker_controller = mMarkerController]
    {
        return marker_controller->GetSelecterMarker();

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

    auto&& marker_ctlr = mMarkerController;
    auto update_markers =
    [playfield, show_window, resource_mgr, controller, marker_ctlr]
    {
        auto marker_registrar = [controller] (ExpansionMarker::Ptr marker)
        { return controller->AddEntity(marker); };

        auto marker_bulk_deleter = [controller] (std::span<uid::Uid> ids)
        { controller->RemoveEntityBulk(ids); };

        marker_ctlr->RemoveExcessMarkers(playfield, marker_bulk_deleter);
        marker_ctlr->CreateMissingMarkers(playfield,
                                          marker_registrar,
                                          show_window,
                                          resource_mgr);
        marker_ctlr->TranslateMarkers(playfield);
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

inline bool subviewHandleEvent([[maybe_unused]]ExpansionSubview& subview,
                               [[maybe_unused]]GameController::Ptr controller,
                               [[maybe_unused]]const sf::Event& event)
{
    return false;
}

inline void subviewUpdate([[maybe_unused]]ExpansionSubview& subview,
                          [[maybe_unused]]GameController::Ptr controller,
                          [[maybe_unused]]float update_delta_seconds)
{
}

} // namespace OpenLabora

#endif // EXPANSIONSUBVIEW_HPP_
