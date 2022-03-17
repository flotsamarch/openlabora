#ifndef GCMAINMENU_HPP_
#define GCMAINMENU_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"
#include "AppState/StateIds.hpp"

namespace OpenLabora
{

class Model;

// Game controller for Main Menu state
class GCMainMenu final
{
public:
    using Ptr = std::shared_ptr<GCMainMenu>;

    PtrView<IApplication<StateIdsVariant>> mApp;
    PtrView<Model> mModel;
    IResourceManager::Ptr mResManager;

    GCMainMenu(PtrView<IApplication<StateIdsVariant>>,
               IResourceManager::Ptr,
               PtrView<Model>);

    void HandleEvent(const sf::Event&);

    void Update(const float update_delta_seconds);

    void HandleWindowResize(const sf::Vector2u&) {};
};

} // namespace OpenLabora

#endif // GCMAINMENU_HPP_
