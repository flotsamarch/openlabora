#ifndef UISCOMMON_HPP_
#define UISCOMMON_HPP_

#include <SFGUI/Widget.hpp>
#include "UiState.hpp"
#include "game/Plot.hpp"

// Base class for states that implement gameplay
class UISCommon : public UiState
{
    bool bIsMenuHidden{ true };
    std::vector<sfg::Widget::Ptr> mMenuWidgets;
protected:
    void HandleEventCommon(const sf::Event&);

    void UpdateCommon(const float secondsSinceLastUpdate);

public:
    UISCommon(std::shared_ptr<State>, const sf::VideoMode&);
    virtual ~UISCommon() noexcept = 0;

    void HandleEvent(const sf::Event&) override;

    void Update(const float secondsSinceLastUpdate) override;

    bool DrawSelectPlotWindow(Plot::PlotType, bool push_front,
                              const sf::Vector2f position);
};

inline UISCommon::~UISCommon() noexcept {};

#endif // UISCOMMON_HPP_
