#ifndef GVDUEL_HPP_
#define GVDUEL_HPP_

#include "GameState/Views/GameView.hpp"

namespace OpenLabora
{

class GameController;
class AppStateManager;
class Model;

class GVDuel final : public GameView
{
public:
    GVDuel(std::shared_ptr<AppStateManager>,
           std::shared_ptr<IGameController>,
           std::shared_ptr<const Model>);
};

} // namespace OpenLabora


#endif // GVDUEL_HPP_
