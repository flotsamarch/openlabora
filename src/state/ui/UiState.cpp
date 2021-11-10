#include "state/ui/UiState.hpp"

#include "Application.hpp"
#include "Renderer.hpp"

Renderer& UiState::GetRenderer() & noexcept
{
    return mState.GetApplication().GetRenderer();
}

sfg::Desktop& UiState::GetDesktop() & noexcept
{
    return GetRenderer().GetDesktop();
}

void UiState::AddWidgetToDesktop(sfg::Widget::Ptr widget)
{
    mWidgets.push_back(widget);
    mState.GetApplication().GetRenderer().GetDesktop().Add(widget);
}

void UiState::RemoveAllWidgets()
{
    mState.GetApplication().GetRenderer().RemoveWidgets(mWidgets.begin(),
                                                        mWidgets.end());
}
