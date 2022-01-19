#ifndef GCDUEL_HPP_
#define GCDUEL_HPP_

#include "GameState/Controllers/GameController.hpp"

namespace OpenLabora
{

class GCDuel final : public GameController
{
public:
    GCDuel(std::shared_ptr<AppStateManager>,
           std::shared_ptr<Model>);
};

} // namespace OpenLabora

#endif // GCDUEL_HPP_
