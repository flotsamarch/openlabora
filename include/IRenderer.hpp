#ifndef IRENDERER_HPP_
#define IRENDERER_HPP_

#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFGUI/Widget.hpp>

namespace OpenLabora
{

class IRenderer
{
public:
    virtual ~IRenderer() {};

    virtual bool IsWindowOpen() const = 0;

    virtual bool PollEvent(sf::Event&) = 0;

    virtual void Clear() = 0;

    virtual void Draw(const sf::Drawable&) = 0;

    virtual void Update(const sf::View&) = 0;

    virtual void HandleEvent(const sf::Event&) = 0;

    virtual void Display() = 0;

    virtual sf::Vector2u GetWindowSize() const = 0;
};

} // namespace OpenLabora

#endif // IRENDERER_HPP_
