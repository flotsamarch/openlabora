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

#ifndef GCFINAL_HPP_
#define GCFINAL_HPP_

#include "IApplication.hpp"
#include "Misc/PtrView.hpp"
#include "Resource/IResourceManager.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Model/Model.hpp"

namespace open_labora
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

} // namespace open_labora

#endif // GCFINAL_HPP_
