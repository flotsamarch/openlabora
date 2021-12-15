#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Window.hpp>
#include <string_view>
#include <memory>
#include "IRenderer.hpp"
#include "GUI/IDesktop.hpp"

template<class TDesktop, class TGui, class TWindow>
class Renderer final : public IRenderer
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "OpenLabora" };
    TWindow mWindow;
    TGui mSfgui;
    TDesktop mDesktop;
    sf::View mView;
    sf::VideoMode mVideoMode{ *sf::VideoMode::getFullscreenModes().begin() };
    bool bWindowClosureRequested { false };

public:
    Renderer();
    ~Renderer() noexcept;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    bool IsWindowOpen() const override { return mWindow.isOpen(); };

    bool PollEvent(sf::Event& evt) override
    { return !bWindowClosureRequested && mWindow.pollEvent(evt); };

    void RequestCloseWindow() noexcept override
    { bWindowClosureRequested = true; };

    // Must be called before Draw()
    void Clear() override;

    void Draw(sf::Sprite) override;

    // Must be called after Draw()
    void Update(float secondsSinceLastUpdate) override;

    void HandleEvent(const sf::Event& evt) override;

    void AddWidgetToDesktop(sfg::Widget::Ptr) override;

    void RemoveWidgets(std::vector<sfg::Widget::Ptr>::iterator begin,
        std::vector<sfg::Widget::Ptr>::iterator end) override;

    sf::VideoMode GetVideoMode() override { return mVideoMode; }

    void MoveView(float offset_x, float offset_y) override
        { mView.move(-offset_x, -offset_y); }

    void MoveView(const sf::Vector2f& offset) override { mView.move(-offset); }

    // Adjust point on screen to global space coordinate
    sf::Vector2f mapPixelToCoords(const sf::Vector2i& point) override
        { return mWindow.mapPixelToCoords(point); }

    // Adjust global space coordinate to a point on screen
    sf::Vector2i mapCoordsToPixel(const sf::Vector2f& point) override
        { return mWindow.mapCoordsToPixel(point); }
};

template<class TDesktop, class TGui, class TWindow>
Renderer<TDesktop, TGui, TWindow>::Renderer() :
    mDesktop { TDesktop{} },
    mSfgui { TGui{} },
    mWindow { TWindow{} }

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

template<class TDesktop, class TGui, class TWindow>
Renderer<TDesktop, TGui, TWindow>::~Renderer() noexcept
{
    mWindow.close();
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::Clear()
{
    mWindow.clear();
    mWindow.setView(mView);
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::Draw(sf::Sprite sprite)
{
    mWindow.draw(sprite);
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::AddWidgetToDesktop(sfg::Widget::Ptr
                                                           widget)
{
    mDesktop.Add(widget);
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::RemoveWidgets(
    std::vector<sfg::Widget::Ptr>::iterator begin,
    std::vector<sfg::Widget::Ptr>::iterator end)
{
    for (auto&& widget = begin; widget < end; ++widget) {
        mDesktop.Remove(*widget);
    }
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::Update(float secondsSinceLastUpdate)
{
    mDesktop.Update(secondsSinceLastUpdate);
    mSfgui.Display(mWindow);
    mWindow.display();
}

template<class TDesktop, class TGui, class TWindow>
void Renderer<TDesktop, TGui, TWindow>::HandleEvent(const sf::Event& evt)
{
    mDesktop.HandleEvent(evt);
}

#endif // RENDERER_HPP_
