#ifndef GSDUELHOTSEAT_HPP_
#define GSDUELHOTSEAT_HPP_

#include "GameState.hpp"
#include "game/Location.hpp"
#include "game/Playfield.hpp"

class GSDuelHotSeat final : public GameState
{
public:
    GSDuelHotSeat(std::shared_ptr<State>);

    void HandleEventImpl(const sf::Event& evt) override final;

    void Update(const float secondsSinceLastUpdate) override final;

    void EnableBuildMode(Location::LocationType);
};

#endif // GSDUELHOTSEAT_HPP_
