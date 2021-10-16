#ifndef BASESTATE_HPP_
#define BASESTATE_HPP_

#include <SFML/Window/Event.hpp>

class BaseState
{
protected:
    bool bIsComplete{ false };
public:
    BaseState() = default;
    virtual ~BaseState() = default;
    virtual void HandleEvent(const sf::Event& evt) = 0;
    virtual void Update() = 0;
    inline bool IsComplete() const { return bIsComplete; };
};

#endif // BASESTATE_HPP_
