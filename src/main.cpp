#include <iostream>
#include <SFGUI/SFGUI.hpp>
#include "Application.hpp"
#include "Renderer.hpp"
#include "GUI/Desktop.hpp"
#include "state/AppStateDefs.hpp"
#include "state/gs/GSMainMenu.hpp"
#include "state/UI/UISMainMenu.hpp"
#include "resource/ResourceManager.hpp"

namespace
{
    template<class TResMgr>
    struct ResMgrType{
        using res_mgr_t = TResMgr;
    };

    using DefaultResMgr = ResMgrType<ResourceManager>;

    using SfmlRenderer = RendererDefs::RendererType
        <Renderer<Desktop, sfg::SFGUI, sf::RenderWindow>>;
}

int main()
{
    Application app{ SfmlRenderer{}, DefaultResMgr{},
        AppStateDefs::MainMenuState{} };
    return app.run();
}
