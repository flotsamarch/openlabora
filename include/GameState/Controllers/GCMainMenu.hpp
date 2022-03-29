#ifndef GCMAINMENU_HPP_
#define GCMAINMENU_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/NoModel.hpp"

namespace OpenLabora
{

// Game controller for Main Menu state
class GCMainMenu final
{
public:
    using Ptr = std::shared_ptr<GCMainMenu>;

    PtrView<IApplication<StateIdsVariant>> mApp;
    NoModel::Ptr mModel;
    IResourceManager::Ptr mResManager;

    GCMainMenu(PtrView<IApplication<StateIdsVariant>>,
               IResourceManager::Ptr,
               NoModel::Ptr);

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);
};

} // namespace OpenLabora

#endif // GCMAINMENU_HPP_
