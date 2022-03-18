#ifndef GCDUEL_HPP_
#define GCDUEL_HPP_

#include "GameState/Controllers/GameController.hpp"
#include "Resource/IResourceManager.hpp"

namespace OpenLabora
{

class GCDuel final : public GameController
{
public:
    using Ptr = std::shared_ptr<GCDuel>;

    GCDuel(PtrView<IApplication<StateIdsVariant>>,
           IResourceManager::Ptr,
           Model::Ptr);
};

} // namespace OpenLabora

#endif // GCDUEL_HPP_
