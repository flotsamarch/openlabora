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

#ifndef GVDUEL_HPP_
#define GVDUEL_HPP_

#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "GameState/Views/GameView.hpp"
#include "GameState/Controllers/GCDuel.hpp"
#include "IApplication.hpp"
#include "AppState/StateIds.hpp"

namespace OpenLabora
{

class GameController;
class Model;

class GVDuel final : public GameView
{
public:
    using Ptr = std::unique_ptr<GVDuel>;

    GVDuel(PtrView<IApplication<StateIdsVariant>>,
           GameWindow<tgui::GuiSFML, sf::RenderWindow>,
           std::shared_ptr<GCDuel>,
           Model::PtrConst);
};

} // namespace OpenLabora


#endif // GVDUEL_HPP_
