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

    void UpdateCommon(const float secondsSinceLastUpdate);

    void HandleEventCommon(const sf::Event& evt) {
        mDesktop.HandleEvent(evt);
    }
public:
    UiState(std::shared_ptr<State> state, const sf::VideoMode& vm) :
        mState{ state },
        mVideoMode{ vm } {};

    // inline
    ~UiState() noexcept {
        mDesktop.RemoveAll();
        mDesktop.Refresh();
    };

    void HandleEvent(const sf::Event& evt) override {
        HandleEventCommon(evt);
    };

    void Update(const float secondsSinceLastUpdate) override
        { UpdateCommon(secondsSinceLastUpdate); };
};

#endif // UISTATE_HPP_
