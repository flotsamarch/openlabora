#ifndef GSCOMMON_HPP_
#define GSCOMMON_HPP_

#include "GameState.hpp"
#include "game/Tile.hpp"

class GSCommon : public GameState
{
public:
    enum PlayerAffiliation { Player1, Player2, Player3, Player4 };

protected:
    std::array<std::shared_ptr<Playfield>, 4> mPlayfields;

    std::shared_ptr<Location> mBuildGhost;
    // LocationArray mLocations;

    bool bBuildModeEnabled{ false };
    bool bPaused{ false };

    int mMouseX = 0, mMouseY = 0;
    float mMouseDeltaX = 0, mMouseDeltaY = 0; // Delta between frames

    // Has to be called in every derived's HandleEvent()
    void HandleEventCommon(const sf::Event& evt, IRenderer&);

    // Has to be called in every derived's Update()
    void UpdateCommon(const float secondsSinceLastUpdate, IRenderer&);
    #if 0
    LocationPtr ChangeLocationTypeAtPoint(const sf::Vector2f&,
                                          const Playfield&,
                                          Location::LocationType);

    LocationPtr GetOrCreateLocationOnTile(const Tile::TileInfo&,
                                           Location::LocationType =
                                           Location::LocationType::Empty);
    #endif

public:
    GSCommon(std::shared_ptr<State>);

    void HandleEvent(const sf::Event&, IRenderer&) override;

    void Update(const float secondsSinceLastUpdate, IRenderer&) override;

    void SetPaused(bool paused) noexcept { bPaused = paused; }

    bool IsPaused() noexcept { return bPaused; }

    void EnableBuildMode(Location::LocationType);

    std::shared_ptr<Playfield> GetActivePlayerPlayfield() const noexcept
    {
        return mPlayfields[Player1];
    }
};

#endif // GSCOMMON_HPP_
