#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <vector>
#include <memory>
#include "Game/IEntity.hpp"
#include "Game/IDrawable.hpp"
#include "Game/ISelectable.hpp"
#include "Game/Location.hpp"
#include "Game/ExpansionMarker.hpp"

namespace OpenLabora
{

class Model
{
public:
    enum PlayerAffiliation { Player1, Player2, Player3, Player4 };
    static constexpr uint32_t kMaxPlayers = 4;

    sf::View mMainView;
    sf::Vector2u mWindowSize;

    bool bBuildModeEnabled{ false };
    bool bPaused{ false };

    std::vector<std::shared_ptr<IEntity>> mEntities;
    std::vector<std::shared_ptr<IDrawable>> mDrawableEntities;
    std::vector<std::shared_ptr<ISelectable>> mSelectableEntities;

    std::array<std::shared_ptr<Playfield>, kMaxPlayers> mPlayfields;
    std::shared_ptr<Location> mBuildGhost;
};

} // namespace OpenLabora

#endif // MODEL_HPP_
