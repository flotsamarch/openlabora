#ifndef INGAMEBUTTON_HPP_
#define INGAMEBUTTON_HPP_

#include <memory>
#include <SFGUI/Button.hpp>
#include "state/State.hpp"

// Button for use in classes derived from GSCommon
// It tells gamestate when mouse entered and left its bounds by switching flag
class IngameButton final : public sfg::Button
{
    std::weak_ptr<::State> mState;
private:
    IngameButton() = default;
    void SetGameState(std::shared_ptr<::State>);
public:
    using Ptr = std::shared_ptr<IngameButton>;

    static Ptr Create(std::shared_ptr<::State>, const sf::String& label = L"" );
};


#endif // INGAMEBUTTON_HPP_
