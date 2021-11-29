#include "state/ui/UiState.hpp"

#include <cassert>

#include "IRenderer.hpp"
#include "IApplication.hpp"
#include "state/State.hpp"

IRenderer* UiState::GetRenderer() const
{
    if (mState.expired()) {
        // Should only happen on program termination
        throw std::runtime_error("State is no longer valid");
    }
    return mState.lock()->GetApp().GetRenderer();
}

IDesktop& UiState::GetDesktop() &
{
    return GetRenderer()->GetDesktop();
}

void UiState::AddWidgetToDesktop(sfg::Widget::Ptr widget)
{
    mWidgets.push_back(widget);
    GetDesktop().Add(widget);
}

void UiState::RemoveAllWidgets()
{
    GetDesktop().RemoveWidgets(mWidgets.begin(), mWidgets.end());
}
