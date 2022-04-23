#ifndef GVFINAL_HPP_
#define GVFINAL_HPP_

#include <memory>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include "GameState/Model/Model.hpp"
#include "IApplication.hpp"
#include "GameWindow.hpp"
#include "AppState/StateIds.hpp"
#include "GameState/Controllers/GCFinal.hpp"

namespace OpenLabora
{

// A view indicating that app has reached its final state
class GVFinal final
{
public:
    using Ptr = std::unique_ptr<GVFinal>;

    // No need for actual arguments here, we ignore them anyway
    template <typename... Args>
    GVFinal([[maybe_unused]]Args&&... args) {};

    void HandleEvent(const sf::Event&) {};

    void Update(const float) {};
};

} // namespace OpenLabora

#endif // GVFINAL_HPP_
