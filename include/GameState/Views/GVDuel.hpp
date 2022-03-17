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
    GVDuel(PtrView<IApplication<StateIdsVariant>>,
           PtrView<tgui::GuiSFML>,
           std::shared_ptr<GCDuel>,
           PtrView<const Model>);
};

} // namespace OpenLabora


#endif // GVDUEL_HPP_
