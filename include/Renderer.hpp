#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Window.hpp>
#include <string_view>
#include <memory>
#include "IRenderer.hpp"

namespace OpenLabora
{

class Renderer final : public IRenderer
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "OpenLabora" };
    sf::RenderWindow mWindow;
    sfg::SFGUI mSfgui;
    sf::VideoMode mVideoMode{ *sf::VideoMode::getFullscreenModes().begin() };

public:
    Renderer();
    ~Renderer() noexcept;

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    bool IsWindowOpen() const override { return mWindow.isOpen(); };

    bool PollEvent(sf::Event& evt) override
    { return IsWindowOpen() && mWindow.pollEvent(evt); };

    void Update(const sf::View& view) override
    { mWindow.setView(view); }

    // Must be called before Draw()
    void Clear() override;

    void Draw(const sf::Drawable&) override; // TODO provide model

    void HandleEvent(const sf::Event&) override;

    // Must be called after Draw()
    void Display() override;

    sf::Vector2u GetWindowSize() const override { return mWindow.getSize(); }
};

} // namespace OpenLabora

#endif // RENDERER_HPP_
