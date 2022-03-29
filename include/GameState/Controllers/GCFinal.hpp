#ifndef GCFINAL_HPP_
#define GCFINAL_HPP_

#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Model.hpp"

namespace OpenLabora
{

// A controller indicating that app has reached its final state
class GCFinal final
{
public:
    using Ptr = std::shared_ptr<GCFinal>;

    // No need for actual arguments here, we ignore them anyway
    template <typename... Args>
    GCFinal([[maybe_unused]]Args&&... args) {};

    void HandleEvent(const sf::Event&) {};

    void Update(const float) {};
};

} // namespace OpenLabora

#endif // GCFINAL_HPP_
