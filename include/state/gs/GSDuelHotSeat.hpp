#ifndef GSDUELHOTSEAT_HPP_
#define GSDUELHOTSEAT_HPP_

#include "GameState.hpp"

class GSDuelHotSeat final : public GameState
{
public:
    GSDuelHotSeat(State&);
    virtual ~GSDuelHotSeat() override final = default;
    virtual void HandleEvent(const sf::Event& evt) override final;
    virtual void Update(const float secondsSinceLastUpdate) override final;
};

#endif // GSDUELHOTSEAT_HPP_
