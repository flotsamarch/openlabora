#ifndef IUISTATE_HPP_
#define IUISTATE_HPP_

#include <SFML/Window/Event.hpp>

class IUiState
{
public:
    virtual ~IUiState() noexcept {};

    virtual void HandleEvent(const sf::Event&) = 0;

    virtual void Update(const float secondsSinceLastUpdate) = 0;
};

#endif // IUISTATE_HPP_
