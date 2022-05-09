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
