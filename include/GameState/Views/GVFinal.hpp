#ifndef GVFINAL_HPP_
#define GVFINAL_HPP_

#include <memory>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "GameState/Model.hpp"
#include "IApplication.hpp"
#include "GameWindow.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

struct NoModel;

// A view indicating that app has reached its final state
class GVFinal final
{
public:
    using Ptr = std::unique_ptr<GVFinal>;

    GVFinal(PtrView<IApplication<StateIdsVariant>>,
            GameWindow<tgui::GuiSFML, sf::RenderWindow>,
            std::shared_ptr<GCFinal>,
            NoModel::CPtr) {};

    void HandleEvent(const sf::Event&) {};

    void Update(const float) {};

    void HandleWindowResize(const sf::Vector2u&) {};
};

} // namespace OpenLabora

#endif // GVFINAL_HPP_
