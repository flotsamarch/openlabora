#ifndef FINALSTATE_HPP_
#define FINALSTATE_HPP_

#include <state/GameState.hpp>

class FinalState final : public GameState
{
public:
    FinalState() { bHasFinished = true; };
    virtual ~FinalState() override final = default;
    virtual void HandleEvent([[maybe_unused]] const sf::Event& evt) override final {};
    virtual void Update() override final {};
};

#endif // FINALSTATE_HPP_
