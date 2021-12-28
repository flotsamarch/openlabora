#ifndef IGAMESTATE_HPP_
#define IGAMESTATE_HPP_

#include <SFML/Window/Event.hpp>
#include <span>
#include "game/IDrawable.hpp"
#include "IRenderer.hpp"

class IGameState
{
public:
    using DrawableSpan = std::span<std::weak_ptr<IDrawable>>;
    virtual ~IGameState() noexcept = 0;

    virtual void HandleEvent(const sf::Event&, IRenderer&) = 0;

    virtual void Update(const float secondsSinceLastUpdate, IRenderer&) = 0;

    virtual DrawableSpan GetDrawableObjectsSpan() noexcept = 0;
};

inline IGameState::~IGameState() noexcept {};

#endif // IGAMESTATE_HPP_
