// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef RENDERER_HPP_
#define RENDERER_HPP_

#include <SFML/Graphics.hpp>
#include <TGUI/Core.hpp>
#include <TGUI/Backends/SFML.hpp>
#include <string_view>
#include <memory>
#include <utility>
#include "Misc/PtrView.hpp"

namespace open_labora
{


/**
 * Class that is responsible for drawing things on screen
 *
 * @tparam TGui - GUI library class
 * @tparam TWindow - Render window class
 */
template<class TGui, class TWindow>
class Renderer final
{
    static constexpr int kFramerateLimit{ 144 };
    static constexpr std::string_view kWindowName{ "open_labora" };
    PtrView<TWindow> mWindow;
    PtrView<TGui> mGui;
    sf::VideoMode mVideoMode{ *sf::VideoMode::getFullscreenModes().begin() };

public:
    Renderer(PtrView<TGui>, PtrView<TWindow>);
    ~Renderer() { if (mWindow->isOpen()) mWindow->close(); }

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    bool IsWindowOpen() const { return mWindow->isOpen(); };

    std::optional<sf::Event> PollEvent() const;

    // Must be called before Draw()
    void Clear() { mWindow->clear(); }

    void Draw(const sf::Drawable& drawable) { mWindow->draw(drawable); }

    // Must be called after Draw()
    void Display();

    // @return true if event was handled in GUI, false otherwise
    bool HandleEvent(const sf::Event&);

    void RemoveAllWidgets() { mGui->removeAllWidgets(); }
};

template<class TGui, class TWindow>
Renderer<TGui, TWindow>::Renderer(PtrView<TGui> gui, PtrView<TWindow> window)
    : mGui{ gui }, mWindow{ window }
{
    mWindow->create(mVideoMode,
                   std::string(kWindowName),
                   sf::Style::Fullscreen);
    mWindow->setFramerateLimit(kFramerateLimit);
    mWindow->setVerticalSyncEnabled(true);

    mGui->setTarget(*mWindow.Get());

    mWindow->resetGLStates();
}

template<class TGui, class TWindow>
std::optional<sf::Event> Renderer<TGui, TWindow>::PollEvent() const
{
    sf::Event event;
    if (!IsWindowOpen() || !mWindow->pollEvent(event)) {
        return std::nullopt;
    }
    return event;
};

template<class TGui, class TWindow>
void Renderer<TGui, TWindow>::Display()
{
    mGui->draw();
    mWindow->display();
}

template<class TGui, class TWindow>
bool Renderer<TGui, TWindow>::HandleEvent(const sf::Event& evt)
{
    bool result = mGui->handleEvent(evt);
    if (evt.type == sf::Event::Closed) {
        mWindow->close();
    }
    return result;
}

} // namespace open_labora

#endif // RENDERER_HPP_
