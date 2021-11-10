#include "state/gs/GSDuelHotSeat.hpp"
#include "state/StateMachine.hpp"
#include "Application.hpp"

GSDuelHotSeat::GSDuelHotSeat(State& state) : GameState{ state }
{
}

void GSDuelHotSeat::HandleEvent([[maybe_unused]]const sf::Event& evt)
{
    return;
}

void GSDuelHotSeat::Update([[maybe_unused]]const float secondsSinceLastUpdate)
{
    return;
}
