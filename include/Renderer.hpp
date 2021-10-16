#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

class Renderer final
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "OpenLabora" };
    sf::RenderWindow mWindow;
    sfg::SFGUI sfgui;
    bool bWindowClosureRequested { false };
public:
    Renderer();
    ~Renderer();
    Renderer(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    bool IsWindowOpen() const { return mWindow.isOpen(); };
    bool PollEvent(sf::Event& evt) { return !bWindowClosureRequested && mWindow.pollEvent(evt); };
    void RequestCloseWindow() { bWindowClosureRequested = true; };
};

#endif // RENDERER_HPP_
