#include <iostream>
#include "Application.hpp"
#include "Renderer.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/UI/UISMainMenu.hpp"
#include "resource/ResourceManager.hpp"

int main()
{
    auto renderer = std::make_unique<Renderer>();
    Application app{ AppStateDefs::MainMenuState{},
        std::move(renderer)
    };

    return app.run();
}
