#include <iostream>
#include "Application.hpp"
#include "Renderer.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/UI/UISMainMenu.hpp"
#include "resource/ResourceManager.hpp"
#include "GUI/Desktop.hpp"

int main()
{
    using SfmlRenderer = Renderer<Desktop, sfg::SFGUI, sf::RenderWindow>;

    auto renderer = std::make_unique<SfmlRenderer>();
    auto res_mgr = std::make_unique<ResourceManager>();


    Application app{ AppStateDefs::MainMenuState{},
        std::move(renderer), std::move(res_mgr)
    };

    return app.run();
}
