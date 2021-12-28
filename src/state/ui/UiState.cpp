#include <cassert>

#include "state/ui/UiState.hpp"
#include "state/State.hpp"

void UiState::UpdateCommon(const float secondsSinceLastUpdate)
{
    mDesktop.Update(secondsSinceLastUpdate);
}
