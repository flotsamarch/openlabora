#include <iostream>
#include "Application.hpp"
#include "Renderer.hpp"
#include "AppState/AppStateDefs.hpp"

int main()
{
    using namespace OpenLabora;
    auto renderer = std::make_unique<Renderer>();
    Application app{ AppStateDefs::MainMenuState{},
        std::move(renderer)
    };

    return app.run();
}
