// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <cassert>
#include "GameState/Controllers/GCMainMenu.hpp"

namespace OpenLabora
{

GCMainMenu::GCMainMenu(PtrView<IApplication<StateIdsVariant>> app,
                       IResourceManager::Ptr resource_mgr,
                       NoModel::Ptr model)
    : mApp{ app }, mModel{ model }, mResourceMgr{ resource_mgr } {}

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
            default: {}
        }
    }
}

void GCMainMenu::Update([[maybe_unused]]const float update_delta_seconds) {};

} // namespace OpenLabora
