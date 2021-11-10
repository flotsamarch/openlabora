#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Window.hpp>
#include <memory>

class UiState;
class GameState;

class Renderer final
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "OpenLabora" };
    sf::RenderWindow mWindow;
    sfg::SFGUI mSfgui;
    sfg::Desktop mDesktop;
    sf::VideoMode mVideoMode{ *sf::VideoMode::getFullscreenModes().begin() };
    bool bWindowClosureRequested { false };
public:
    Renderer();
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    bool IsWindowOpen() const { return mWindow.isOpen(); };
    bool PollEvent(sf::Event& evt) { return !bWindowClosureRequested
            && mWindow.pollEvent(evt); };
    void RequestCloseWindow() noexcept { bWindowClosureRequested = true; };
    void Render(const float secondsSinceLastUpdate);
    void HandleEvent(const sf::Event& evt);
    sfg::Desktop& GetDesktop() & noexcept { return mDesktop; }
    sf::VideoMode GetVideoMode() { return mVideoMode; }
    void RemoveWidgets(std::vector<sfg::Widget::Ptr>::iterator begin,
        std::vector<sfg::Widget::Ptr>::iterator end);
};

#endif // RENDERER_HPP_
