#ifndef GSDUELHOTSEAT_HPP_
#define GSDUELHOTSEAT_HPP_

#include "GameState.hpp"

class GSDuelHotSeat final : public GameState
{
public:
    GSDuelHotSeat(std::shared_ptr<State>);

    void HandleEvent(const sf::Event& evt) override final;

    void Update(const float secondsSinceLastUpdate) override final;
};

#endif // GSDUELHOTSEAT_HPP_
