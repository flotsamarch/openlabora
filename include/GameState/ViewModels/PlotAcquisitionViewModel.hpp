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

#ifndef PLOTACQUISITIONVIEWMODEL_HPP_
#define PLOTACQUISITIONVIEWMODEL_HPP_

#include <optional>
#include "Misc/PtrView.hpp"
#include "LibTypedefs.hpp"
#include "ECS/Entity.hpp"
#include "Game/Systems/Events/CreatePlotEvent.hpp"
#include "Game/Systems/Events/UpdateMarkersEvent.hpp"
#include "Game/Components/PositionComponent.hpp"
#include "Game/Components/InteractionAreaComponent.hpp"
#include "Game/Components/SelectableComponent.hpp"
#include "Game/Components/PlotAcquireInfoComponent.hpp"
#include "Game/Components/SignalComponent.hpp"

namespace open_labora
{

template<class TModel>
class PlotAcquisitionViewModel final
{
    using RectangleArea = RectangularInteractionAreaComponent;
    using OptionalEntity = std::optional<Entity>;

    PtrView<TModel> mModel;
    OptionalEntity mSelectedMarker{};

public:
    PlotAcquisitionViewModel(PtrView<TModel> model)
        : mModel{ model }
    {
    }

    void HighlightMarker(const Vector2f& mouse_pos);

    // @return true if any marker has been selected
    bool SelectMarker(const Vector2f& mouse_pos);

    lot::Type GetSelectedMarkerLotType();

    void DeselectMarker();

    // Be sure to change plot_acquisition::AcquirePlotCallback signature when
    // changing this function signature
    plot::AcquireReturnType AcquirePlot(plot::AcquirePlotParams& params);
};

template<class TModel>
void PlotAcquisitionViewModel<TModel>::HighlightMarker(const Vector2f& mouse_pos)
{
    auto&& registry = mModel->GetRegistry();
    registry.template ForJoinedComponents<PlotAcquireInfoComponent,
                                          PositionComponent,
                                          RectangleArea,
                                          SignalComponent>(
    [&mouse_pos]
    (auto&&,
     const PlotAcquireInfoComponent&,
     const PositionComponent& position,
     const RectangleArea& area,
     SignalComponent& signals)
    {
        auto point_local = Vector2f{ mouse_pos } - Vector2f{ position };
        if (!area.IsPointInArea(point_local)) {
            signals.Emit(signals::kOnLeave);
            return;
        }

        signals.Emit(signals::kOnEnter);
    });
}

template<class TModel>
bool PlotAcquisitionViewModel<TModel>::SelectMarker(const Vector2f& mouse_pos)
{
    bool has_been_selected{ false };

    auto&& registry = mModel->GetRegistry();
    registry.template ForJoinedComponents<PlotAcquireInfoComponent,
                                          PositionComponent,
                                          RectangleArea,
                                          SignalComponent>(
    [&mouse_pos, &selected = mSelectedMarker, &has_been_selected]
    (auto&& marker,
     const PlotAcquireInfoComponent&,
     const PositionComponent& position,
     const RectangularInteractionAreaComponent& area,
     SignalComponent& signals)
    {
        if (selected != std::nullopt) {
            return;
        }

        auto point_local = Vector2f{ mouse_pos } - Vector2f{ position };
        if (!area.IsPointInArea(point_local)) {
            return;
        }

        signals.Emit(signals::kOnSelect);
        selected = marker;
        has_been_selected = true;
    });

    return has_been_selected;
}

template<class TModel>
lot::Type PlotAcquisitionViewModel<TModel>::GetSelectedMarkerLotType()
{
    assert(mSelectedMarker != std::nullopt);
    auto marker = mSelectedMarker.value();
    return marker.GetComponent<PlotAcquireInfoComponent>().lot_type;
}

template<class TModel>
void PlotAcquisitionViewModel<TModel>::DeselectMarker()
{
    if (mSelectedMarker != std::nullopt) {
        auto marker = mSelectedMarker.value();
        marker.GetComponent<SignalComponent>().Emit(signals::kOnDeselect);
        mSelectedMarker = std::nullopt;
    }
}

template<class TModel>
plot::AcquireReturnType PlotAcquisitionViewModel<TModel>
::AcquirePlot(plot::AcquirePlotParams& params)
{
    assert(mSelectedMarker != std::nullopt);

    auto&& registry = mModel->GetRegistry();
    auto marker = mSelectedMarker.value();
    const auto info = marker.GetComponent<PlotAcquireInfoComponent>();
    const auto lot_type = info.lot_type;
    const auto to_top = info.add_to_top;
    const auto& position = marker.GetComponent<PositionComponent>();
    DeselectMarker();

    const auto index = static_cast<int>(params.type_id);
    auto plot = plot::getPlots(info.lot_type)[index];

    auto event = CreatePlotEvent{ plot, lot_type, to_top, position};
    registry.HandleEvent(event);
    registry.HandleEvent(UpdateMarkersEvent{});
}

} // namespace open_labora

#endif // PLOTACQUISITIONVIEWMODEL_HPP_
