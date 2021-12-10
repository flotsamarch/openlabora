#ifndef GSDUELHOTSEAT_HPP_
#define GSDUELHOTSEAT_HPP_

#include "GameState.hpp"
#include "game/Location.hpp"
#include "game/Playfield.hpp"

class GSDuelHotSeat final : public GameState
{
    Location::LocationType mBuildType{ Location::LocationType::Forest };
    bool bBuildMode{ false };
    Location* mBuildGhost;
    Playfield* mPlayfield;

public:
    GSDuelHotSeat(std::shared_ptr<State>);

    void HandleEventImpl(const sf::Event& evt) override final;

    void Update(const float secondsSinceLastUpdate) override final;
};

#endif // GSDUELHOTSEAT_HPP_
