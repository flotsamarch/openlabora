#include <SFGUI/Container.hpp>
#include <iostream>
#include "Renderer.hpp"
#include "state/gs/GameState.hpp"
#include "state/ui/UiState.hpp"

Renderer::Renderer()
{
    mWindow.create(mVideoMode,
                   std::string(kWindowName),
                   sf::Style::Fullscreen);
    mWindow.setFramerateLimit(kFramerateLimit);
    mWindow.setVerticalSyncEnabled(true);

    // Some SFGUI hack
    // TODO remove once we start using SFML for rendering
    mWindow.resetGLStates();
}

Renderer::~Renderer()
{
    mWindow.close();
}

void Renderer::Render(float secondsSinceLastUpdate)
{
    mDesktop.Update(secondsSinceLastUpdate);
    mWindow.clear();
    mSfgui.Display(mWindow);
    mWindow.display();
}

void Renderer::HandleEvent(const sf::Event& evt)
{
    mDesktop.HandleEvent(evt);
}

void Renderer::RemoveWidgets(std::vector<sfg::Widget::Ptr>::iterator begin,
                             std::vector<sfg::Widget::Ptr>::iterator end)
{
    for (auto widget = begin; widget != end; widget++) {
        mDesktop.Remove(*widget);
    }
}
