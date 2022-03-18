#ifndef GAMEWINDOW_HPP_
#define GAMEWINDOW_HPP_

#include "Misc/PtrView.hpp"
#include "SFML/Graphics/View.hpp"

namespace OpenLabora
{

// Interface and wrapper for window methods needed during gameplay
// @tparam TGui - A GUI library class
// @tparam TWindow - Render window class
template<class TGui, class TWindow>
class GameWindow final
{
    PtrView<TWindow> mWindow;
    PtrView<TGui> mGui;

public:
    GameWindow(PtrView<TGui> gui, PtrView<TWindow> window)
        : mWindow{ window }, mGui{ gui } {};

    // Set View - ingame region which is drawn and its position on the screen
    void SetView(const sf::View& view) { mWindow->setView(view); }

    decltype(auto) GetView() const { return mWindow->getView(); }

    auto GetSize() { return mWindow->getSize(); } const

    auto MapScreenToWorldCoords(const sf::Vector2i& point) const
    { mWindow->mapPixelToCoords(point); }

    auto MapWorldToScreenCoords(const sf::Vector2f& coord) const
    { mWindow->mapCoordsToPixel(coord); }
};

} // namespace OpenLabora

#endif // GAMEWINDOW_HPP_
