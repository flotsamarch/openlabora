#ifndef UISTATE_HPP_
#define UISTATE_HPP_

#include <memory>
#include <vector>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Widget.hpp>
#include <SFML/Window/VideoMode.hpp>
#include "state/ui/IUiState.hpp"

class State;

// General UI logic base class
class UiState : public IUiState
{
protected:
    std::weak_ptr<State> mState;
    sfg::Desktop mDesktop;
    const sf::VideoMode& mVideoMode;
public:
    UiState(std::shared_ptr<State> state, const sf::VideoMode& vm)
        : mState{ state }, mVideoMode{ vm } {};

    virtual ~UiState() noexcept
    {
        mDesktop.RemoveAll();
        mDesktop.Refresh();
    };

    void HandleEvent(const sf::Event& evt) override
    {
        mDesktop.HandleEvent(evt);
    };

    void Update(const float secondsSinceLastUpdate) override;
};

#endif // UISTATE_HPP_
