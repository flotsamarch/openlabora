#include "Renderer.hpp"

namespace OpenLabora
{

Renderer::Renderer()
{
    mWindow.create(mVideoMode,
                   std::string(kWindowName),
                   sf::Style::Fullscreen);
    mWindow.setFramerateLimit(kFramerateLimit);
    mWindow.setVerticalSyncEnabled(true);

    mWindow.resetGLStates();
}

Renderer::~Renderer() noexcept
{
    mWindow.close();
}

void Renderer::Clear()
{
    mWindow.clear();
}

void Renderer::Draw(const sf::Drawable& drawable)
{
    mWindow.draw(drawable);
}

void Renderer::Display()
{
    mSfgui.Display(mWindow);
    mWindow.display();
}

void Renderer::HandleEvent(const sf::Event& evt)
{
    if (evt.type == sf::Event::Closed) {
        mWindow.close();
    }
}

} // namespace OpenLabora
