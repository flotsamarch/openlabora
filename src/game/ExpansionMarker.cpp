#include "AppState/AppStateManager.hpp"
#include "Game/ExpansionMarker.hpp"
#include "resource/IResourceManager.hpp"

namespace OpenLabora
{

ExpansionMarker::ExpansionMarker(const Plot& plot,
                                 bool moves_up)
    : mPlot{ plot }, bMovesUp{ moves_up }
{
    mObject = static_cast<const sf::Sprite&>(mPlot.GetDrawableObject());
    mObject.setColor(sf::Color::Transparent);
}

void ExpansionMarker::OnHover()
{
    if (bWasEntered) {
        return;
    }

    bWasEntered = true;

    mObject.setColor(kHalfTransparent);
}

void ExpansionMarker::OnOut()
{
    if (!bWasEntered) {
        return;
    }

    bWasEntered = false;

    mObject.setColor(sf::Color::Transparent);
}

void ExpansionMarker::Select(std::shared_ptr<AppStateManager> state)
{
    // TODO draw selection window
    // auto&& ui_state = static_cast<UISCommon&>(state->GetUiState());
    // ui_state.DrawCentralPlotSelectionWindow(mPlot.GetType(), bMovesUp);
}

} // namespace OpenLabora
