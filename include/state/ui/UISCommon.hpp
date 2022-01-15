#ifndef UISCOMMON_HPP_
#define UISCOMMON_HPP_

#include <SFGUI/Widget.hpp>
#include <SFGUI/Window.hpp>
#include "UiState.hpp"
#include "game/Plot.hpp"

// Base class for states that implement gameplay
class UISCommon : public UiState
{
    bool bIsMenuHidden{ true };
    bool bIsCentralPlotSelectionHidden{ true };
    bool bExtendUpwards{ false };
    std::vector<sfg::Widget::Ptr> mMenuWidgets;
    sfg::Window::Ptr mCentralPlotSelectionWindow;
    sfg::Window::Ptr mSidePlotSelectionWindow;
protected:
    void HandleEventCommon(const sf::Event&);

    void UpdateCommon(const float secondsSinceLastUpdate);

public:
    UISCommon(std::shared_ptr<State>, const sf::VideoMode&);
    virtual ~UISCommon() noexcept = 0;

    void HandleEvent(const sf::Event&) override;

    void Update(const float secondsSinceLastUpdate) override;

    bool DrawCentralPlotSelectionWindow(Plot::PlotType, bool push_front);

};

inline UISCommon::~UISCommon() noexcept {};

#endif // UISCOMMON_HPP_
