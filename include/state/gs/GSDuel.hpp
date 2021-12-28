#ifndef GSDUEL_HPP_
#define GSDUEL_HPP_

#include "GSCommon.hpp"
#include "game/Location.hpp"
#include "game/Playfield.hpp"

class GSDuel final : public GSCommon
{
public:
    GSDuel(std::shared_ptr<State>);

    void HandleEvent(const sf::Event&, IRenderer&) override;

    void Update(const float secondsSinceLastUpdate, IRenderer&) override;

    void EnableBuildMode(Location::LocationType);
};

#endif // GSDUEL_HPP_
