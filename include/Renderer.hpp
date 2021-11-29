#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Window.hpp>
#include <string_view>
#include <memory>
#include "IRenderer.hpp"
#include "GUI/IDesktop.hpp"

namespace RendererDefs
{
    template<class TRenderer>
    struct RendererType
    {
        using renderer_t = TRenderer;
    };
}

template<class TDesktop, class TGui, class TWindow>
class Renderer final : public IRenderer
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "OpenLabora" };
    TWindow mWindow;
    TGui mSfgui;
    TDesktop mDesktop;
    sf::VideoMode mVideoMode{ *sf::VideoMode::getFullscreenModes().begin() };
    bool bWindowClosureRequested { false };
public:
    Renderer();
    ~Renderer() noexcept;

    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    bool IsWindowOpen() const override { return mWindow.isOpen(); };

    bool PollEvent(sf::Event& evt) override
    { return !bWindowClosureRequested && mWindow.pollEvent(evt); };

    void RequestCloseWindow() noexcept override
    { bWindowClosureRequested = true; };

    void Render(const float secondsSinceLastUpdate) override;

    void HandleEvent(const sf::Event& evt) override;

    IDesktop& GetDesktop() & noexcept override { return mDesktop; }

    sf::VideoMode GetVideoMode() override { return mVideoMode; }
};

template<class TDesktop, class TGui, class TWindow>
Renderer<TDesktop, TGui, TWindow>::Renderer() : mDesktop { TDesktop{} },
                                                mSfgui { TGui{} },
                                                mWindow { TWindow{} }
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

template<class TDesktop, class TGui, class TWindow>
Renderer<TDesktop, TGui, TWindow>::~Renderer() noexcept
{
    mWindow.close();
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::Render(float secondsSinceLastUpdate)
{
    mDesktop.Update(secondsSinceLastUpdate);
    mWindow.clear();
    mSfgui.Display(mWindow);
    mWindow.display();
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::HandleEvent(const sf::Event& evt)
{
    mDesktop.HandleEvent(evt);
}

#endif // RENDERER_HPP_
