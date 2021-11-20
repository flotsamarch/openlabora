#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFGUI/Widget.hpp>
#include "GUI/IDesktop.hpp"

class IRenderer
{
public:
    virtual ~IRenderer() noexcept {};

    virtual bool IsWindowOpen() const = 0;

    virtual bool PollEvent(sf::Event&) = 0;

    virtual void RequestCloseWindow() noexcept = 0;

    virtual void Render(const float timeSinceLastUpdate) = 0;

    virtual void HandleEvent(const sf::Event&) = 0;

    virtual IDesktop& GetDesktop() & noexcept = 0;

    virtual sf::VideoMode GetVideoMode() = 0;
};

#endif // IRENDERER_HPP_
