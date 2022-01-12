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

void LandPurchaseMarker::Select(IUiState& ui_state)
{
    auto&& state = static_cast<UISCommon&>(ui_state);
    if (state.DrawSelectPlotWindow(mPlot.GetType(), bMovesUp, mPlot.GetPosition())) {
        Move(0.f, mPlot.GetType() == Plot::PlotType::Central ?
             Tile::kTileHeight : 2 * Tile::kTileHeight);
    }
}
