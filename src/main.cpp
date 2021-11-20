#include <iostream>
#include <SFGUI/SFGUI.hpp>
#include "Application.hpp"
#include "Renderer.hpp"
#include "GUI/Desktop.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/UI/UISMainMenu.hpp"

namespace
{
    using SfmlRenderer = RendererDefs::RendererType
        <Renderer<Desktop, sfg::SFGUI, sf::RenderWindow>>;
}

int main()
{
    Application app{ SfmlRenderer{}, AppStateDefs::MainMenuState{} };
    return app.run();
}
