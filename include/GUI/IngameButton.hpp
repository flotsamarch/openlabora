#ifndef INGAMEBUTTON_HPP_
#define INGAMEBUTTON_HPP_

#include <memory>
#include <SFGUI/Button.hpp>
#include "GameState/Views/IGameView.hpp"

namespace OpenLabora
{

// Button that is compatible with clickable entities
// It sets a corresponding flag when mouse enters or leaves it
// Should be owned only by classes derived from GameView
class IngameButton final : public sfg::Button
{
    IGameView& mGameView;

private:
    IngameButton(IGameView&);
    void SetGameState(IGameView&);

public:
    using Ptr = std::shared_ptr<IngameButton>;

    static Ptr Create(IGameView&, const sf::String& label = L"" );
};

} // namespace OpenLabora

#endif // INGAMEBUTTON_HPP_
