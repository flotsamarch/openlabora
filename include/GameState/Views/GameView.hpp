#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <memory>
#include <vector>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Widget.hpp>
#include <SFGUI/Window.hpp>
#include <SFGUI/Button.hpp>
#include "GameState/Views/IGameView.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "Game/MarkerManager.hpp"
#include "GUI/Utility.hpp"

namespace OpenLabora
{

class GameController;
class AppStateManager;
class Model;

// General UI logic base class
class GameView : public IGameView
{
protected:
    using Window = sfg::Window;
    using Widget = sfg::Widget;
    using Button = sfg::Button;
    static constexpr std::string_view kConfirmButtonLabelYes = "Yes";
    static constexpr std::string_view kConfirmButtonLabelNo = "No";
    static constexpr std::string_view kConfirmWindowText = "Buy plot?";

    static constexpr char kConfirmWindowStyle = Window::Style::BACKGROUND |
                                                Window::Style::TITLEBAR |
                                                Window::Style::SHADOW |
                                                Window::Style::CLOSE;
    std::weak_ptr<AppStateManager> mState;
    std::shared_ptr<GameController> mController;
    std::shared_ptr<const Model> mModel;
    sfg::Desktop mDesktop;

    sf::Vector2i mMouseCoords;
    sf::Vector2f mMouseDelta{ 0.f, 0.f };

    bool bEscMenuHidden{ true };
    std::vector<sfg::Widget::Ptr> mMenuWidgets;
    float mEscMenuColWidth;
    sf::Vector2f mScreenCenter;
    float mEscMenuButtonHeight = 40.f;
    float mEscMenuTotalHeight = mEscMenuButtonHeight;

    std::shared_ptr<Location> mBuildGhost;

    Window::Ptr mPlotConfirmWindow =
        CreateEventConsumingWidget<Window>(mController, kConfirmWindowStyle);
    Button::Ptr mPlotConfirmButton =
        CreateWidget<Button>(kConfirmButtonLabelYes);

    MarkerManager mMarkerManager;
    std::weak_ptr<ExpansionMarker> mSelectedMarker; // Owned by Model

    // These are SFML screenspace<->world coordinate transformation methods
    // They are copied since i cannot pass window around easily
    sf::IntRect TransformViewToWindowCoords(const sf::View&);

    sf::Vector2f MapScreenToWorldCoords(const sf::Vector2i&, const sf::View&);

    sf::Vector2i MapWorldToScreenCoords(const sf::Vector2f&, const sf::View&);

    // Create labelled widgets which are visible during gameplay
    template<CWidget TWidget>
    typename TWidget::Ptr CreateWidget(const std::string_view& label);

public:
    GameView(std::shared_ptr<AppStateManager>,
             std::shared_ptr<GameController>,
             std::shared_ptr<const Model>);

    virtual ~GameView() noexcept;

    void HandleEvent(const sf::Event&) override;

    void Update(const float update_delta_seconds) override;

    void HandleWindowResize(const sf::Vector2u& window_size) override;
};

template<CWidget TWidget>
typename TWidget::Ptr GameView::CreateWidget(const std::string_view& label)
{
    return CreateEventConsumingWidget<TWidget>(mController, std::string{label});
}

} // namespace OpenLabora

#endif // GAMEVIEW_HPP_
