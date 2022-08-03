// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <filesystem>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Application.hpp"
#include "GameWindow.hpp"
#include "Renderer.hpp"
#include "GameState/MainMenuFwd.hpp"
#include "Resource/ResourceManager.hpp"

int main(int, char** argv)
{
    auto path_to_executable = std::filesystem::absolute(argv[0]);

    namespace ol = open_labora;
    ol::Application<tgui::GuiSFML,
                    sf::RenderWindow,
                    ol::GameWindow,
                    ol::Renderer,
                    ol::ResourceManager> app(path_to_executable);

    namespace state = ol::state;
    using MainMenu = state::MainMenu;
    state::changeState<MainMenu>(ol::ApplicationContext::Ptr{ &app },
                                 app.GetGameWindow(),
                                 app.GetResourceMgr());
    return app.run();
}
