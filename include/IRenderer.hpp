#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFGUI/Widget.hpp>

class IRenderer
{
public:
    virtual ~IRenderer() noexcept {};

    virtual bool IsWindowOpen() const = 0;

    virtual bool PollEvent(sf::Event&) = 0;

    virtual void RequestCloseWindow() noexcept = 0;

    virtual void Clear() = 0;

    virtual void Draw(const sf::Drawable&) = 0;

    virtual void Update(float timeSinceLastUpdate) = 0;

    virtual const sf::VideoMode& GetVideoMode() = 0;

    virtual void MoveView(float offset_x, float offset_y) = 0;

    virtual void MoveView(const sf::Vector2f& offset) = 0;

    virtual sf::Vector2f mapPixelToCoords(const sf::Vector2i&) = 0;

    virtual sf::Vector2i mapCoordsToPixel(const sf::Vector2f&) = 0;
};

#endif // IRENDERER_HPP_
