#include <cassert>
#include "GameState/Controllers/GCMainMenu.hpp"

namespace OpenLabora
{

GCMainMenu::GCMainMenu(PtrView<IApplication<StateIdsVariant>> app,
                       IResourceManager::Ptr res_manager,
                       NoModel::Ptr model)
    : mApp{ app }, mResManager{ res_manager }, mModel{ model } {}

void GCMainMenu::HandleEvent(const sf::Event& evt)
{
    if (evt.type == sf::Event::KeyPressed) {
        switch (evt.key.code) {
            case sf::Keyboard::Escape:
            {
                assert(mApp != nullptr);
                mApp->ChangeState(FinalStateId{});
                break;
            }
            // TODO Fix UI: Remove this case
            case sf::Keyboard::N:
            {
                assert(mApp != nullptr);
                mApp->ChangeState(DuelStateId{});
                break;
            }
            default: {}
        }
    }
}

void GCMainMenu::Update([[maybe_unused]]const float update_delta_seconds) {};

} // namespace OpenLabora
