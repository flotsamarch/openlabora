#include <iostream>
#include <filesystem>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Application.hpp"
#include "Renderer.hpp"
#include "AppState/StateIds.hpp"
#include "AppState/Transitions.hpp"
#include "Resource/ResourceManager.hpp"

int main(int, char** argv)
{
    auto path_to_executable = std::filesystem::absolute(argv[0]);

    using namespace OpenLabora;
    Application<tgui::GuiSFML,
                sf::RenderWindow,
                Renderer,
                Transitions,
                State,
                StateIdsVariant,
                ResourceManager> app(path_to_executable);

    return app.run();
}
