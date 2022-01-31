#ifndef GAMEVIEW_HPP_
#define GAMEVIEW_HPP_

#include <memory>
#include <vector>
#include <SFGUI/Desktop.hpp>
#include <SFGUI/Widget.hpp>
#include <SFGUI/Window.hpp>
#include "GameState/Views/IGameView.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "Game/ExpansionMarker.hpp"
#include "GUI/Utility.hpp"

namespace OpenLabora
{

class GameController;
class AppStateManager;
class Model;

// General UI logic base class
class GameView : public IGameView
{
    using MarkerType = ExpansionMarker::MarkerType;
    static constexpr auto kMaxMarkerType =
        static_cast<std::size_t>(MarkerType::Max);
    using MarkerArray =
        std::array<std::shared_ptr<ExpansionMarker>, kMaxMarkerType>;

protected:
    std::weak_ptr<AppStateManager> mState;
    std::shared_ptr<GameController> mController;
    std::shared_ptr<const Model> mModel;
    sfg::Desktop mDesktop;

    sf::Vector2i mMouseCoords;
    sf::Vector2f mMouseDelta{ 0.f, 0.f };

    bool bMouseLeftReleaseHandled{ false };
    bool bEscMenuHidden{ true };
    std::vector<sfg::Widget::Ptr> mMenuWidgets;
    float mEscMenuColWidth;
    sf::Vector2f mScreenCenter;
    float mEscMenuButtonHeight = 40.f;
    float mEscMenuTotalHeight = mEscMenuButtonHeight;

    std::map<Plot::PlotType, MarkerArray> mMarkers;

    sfg::Window::Ptr mCentralPlotSelectionWindow;
    sfg::Window::Ptr mPlotConfirmWindow;

    // These are SFML screenspace<->world coordinate transformation methods
    // They are copied since i cannot pass window around easily
    sf::IntRect TransformViewToWindowCoords(const sf::View&);

    sf::Vector2f MapScreenToWorldCoords(const sf::Vector2i&, const sf::View&);

    sf::Vector2i MapWorldToScreenCoords(const sf::Vector2f&, const sf::View&);

    void RegisterExpansionMarker(std::shared_ptr<ExpansionMarker> marker);

    void UpdateMarkers();

    template<class TWidget, typename... Args>
    requires std::derived_from<TWidget, sfg::Widget>
    typename TWidget::Ptr CreateEventConsumingWidget(Args&&... args);

public:
    GameView(std::shared_ptr<AppStateManager>,
             std::shared_ptr<GameController>,
             std::shared_ptr<const Model>);

    virtual ~GameView() noexcept;

    void HandleEvent(const sf::Event& evt) override;

    void Update(const float update_delta_seconds) override;

    void HandleWindowResize(const sf::Vector2u& window_size) override;
};

template<class TWidget, typename... Args>
requires std::derived_from<TWidget, sfg::Widget>
typename TWidget::Ptr GameView::CreateEventConsumingWidget(Args&&... args)
{
    auto widget = TWidget::Create(std::forward<Args>(args)...);

    auto mouse_left_release_handled =
    [&flag = bMouseLeftReleaseHandled]
    {
        flag = true;
    };

    connect(widget,
            sfg::Widget::OnMouseLeftRelease,
            mouse_left_release_handled);

    if constexpr (std::derived_from<TWidget, sfg::Window>) {
        connect(widget,
                sfg::Window::OnCloseButton,
                mouse_left_release_handled);
    }

    return widget;
};

} // namespace OpenLabora

#endif // GAMEVIEW_HPP_
