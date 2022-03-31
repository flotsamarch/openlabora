#include <iostream>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Application.hpp"
#include "Renderer.hpp"
#include "AppState/StateIds.hpp"
#include "AppState/Transitions.hpp"
#include "Resource/ResourceManager.hpp"

int main()
{
    using namespace OpenLabora;
    Application<tgui::GuiSFML,
                sf::RenderWindow,
                Renderer,
                Transitions,
                State,
                StateIdsVariant,
                ResourceManager> app;

    return app.run();
}
