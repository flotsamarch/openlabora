#include "state/state.hpp"
#include "game/LandPurchaseMarker.hpp"
#include "resource/IResourceManager.hpp"
#include "state/ui/UISCommon.hpp"

LandPurchaseMarker::LandPurchaseMarker(const Plot& plot,
                                       bool moves_up)
    : mPlot{ plot }, bMovesUp{ moves_up }
{
    mObject = static_cast<const sf::Sprite&>(mPlot.GetDrawableObject());
    mObject.setColor(sf::Color::Transparent);
}

void LandPurchaseMarker::OnHover()
{
    if (bWasEntered) {
        return;
    }

    bWasEntered = true;

    mObject.setColor(kHalfTransparent);
}

void LandPurchaseMarker::OnOut()
{
    if (!bWasEntered) {
        return;
    }

    bWasEntered = false;

    mObject.setColor(sf::Color::Transparent);
}

void LandPurchaseMarker::Select(std::shared_ptr<State> state)
{
    auto&& ui_state = static_cast<UISCommon&>(state->GetUiState());
    ui_state.DrawCentralPlotSelectionWindow(mPlot.GetType(), bMovesUp);
}
