#include "Renderer.hpp"

Renderer::Renderer()
{
    mWindow.create(mVideoMode,
                   std::string(kWindowName),
                   sf::Style::Fullscreen);
    mWindow.setFramerateLimit(kFramerateLimit);
    mWindow.setVerticalSyncEnabled(true);
    mView.reset(sf::FloatRect(0.f, 0.f,
                              static_cast<float>(mVideoMode.width),
                              static_cast<float>(mVideoMode.height)));
    mWindow.setView(mView);

    mWindow.resetGLStates();
}

Renderer::~Renderer() noexcept
{
    mWindow.close();
}

void Renderer::Clear()
{
    mWindow.clear();
    mWindow.setView(mView);
}

void Renderer::Draw(const sf::Drawable& drawable)
{
    mWindow.draw(drawable);
}

void Renderer::Update(float secondsSinceLastUpdate)
{
    mSfgui.Display(mWindow);
    mWindow.display();
}
