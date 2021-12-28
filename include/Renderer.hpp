#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Window.hpp>
#include <string_view>
#include <memory>
#include "IRenderer.hpp"

class Renderer final : public IRenderer
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "OpenLabora" };
    sf::RenderWindow mWindow;
    sfg::SFGUI mSfgui;
    sf::View mView;
    sf::VideoMode mVideoMode{ *sf::VideoMode::getFullscreenModes().begin() };
    bool bWindowClosureRequested { false };

public:
    Renderer();
    ~Renderer() noexcept;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    bool IsWindowOpen() const override { return mWindow.isOpen(); };

    bool PollEvent(sf::Event& evt) override
    { return !bWindowClosureRequested && mWindow.pollEvent(evt); };

    void RequestCloseWindow() noexcept override
    { bWindowClosureRequested = true; };

    // Must be called before Draw()
    void Clear() override;

    void Draw(const sf::Drawable&) override;

    // Must be called after Draw()
    void Update(float secondsSinceLastUpdate) override;

    const sf::VideoMode& GetVideoMode() override { return mVideoMode; }

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

#endif // RENDERER_HPP_
