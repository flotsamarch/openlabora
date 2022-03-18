#include <iostream>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Application.hpp"
#include "AppState/StateIds.hpp"
#include "AppState/Transitions.hpp"

int main()
{
    using namespace OpenLabora;
    Application<tgui::GuiSFML, sf::RenderWindow, Transitions, State,
                StateIdsVariant> app;

    return app.run();
}
