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
           Model::CPtr);
};

} // namespace OpenLabora


#endif // GVDUEL_HPP_
