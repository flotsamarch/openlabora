#ifndef GVFINAL_HPP_
#define GVFINAL_HPP_

#include <memory>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "GameState/Model.hpp"
#include "IApplication.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

// A view indicating that app has reached its final state
class GVFinal final
{
public:
    GVFinal(PtrView<IApplication<StateIdsVariant>>,
            PtrView<tgui::GuiSFML>,
            std::shared_ptr<GCFinal>,
            PtrView<const Model>) {};

    void HandleEvent(const sf::Event&) {};

    void Update(const float) {};

    void HandleWindowResize(const sf::Vector2u&) {};
};

} // namespace OpenLabora

#endif // GVFINAL_HPP_
