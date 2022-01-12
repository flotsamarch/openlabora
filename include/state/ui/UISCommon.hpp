#ifndef UISCOMMON_HPP_
#define UISCOMMON_HPP_

#include "UISEscapeMenu.hpp"
#include "game/Plot.hpp"

class UISCommon : public UISEscapeMenu
{
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
