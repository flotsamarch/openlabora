#ifndef GAMESTATE_HPP_
#define GAMESTATE_HPP_

#include <SFML/Window/Event.hpp>

class GameState
{
protected:
    bool bIsComplete{ false };
public:
    GameState() = default;
    virtual ~GameState() = default;
    virtual void HandleEvent(const sf::Event& evt) = 0;
    virtual void Update() = 0;
    inline bool IsComplete() const { return bIsComplete; };
};


#endif // GAMESTATE_HPP_
