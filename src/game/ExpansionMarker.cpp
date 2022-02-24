#include "Game/ExpansionMarker.hpp"
#include "AppState/AppStateManager.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "resource/IResourceManager.hpp"
#include "GUI/Utility.hpp"

namespace OpenLabora
{

namespace
{
    using Widget = sfg::Widget;
}

ExpansionMarker::ExpansionMarker(GameController::Ptr ctlr,
                                 sfg::Window::Ptr window,
                                 sfg::Button::Ptr button,
                                 MarkerType type,
                                 const Plot& plot_top,
                                 const Plot& plot_bottom)
    : ExpansionMarker{ ctlr, window, button, type, plot_top }
{
    mPlotBottom = Plot{ plot_bottom };
}

ExpansionMarker::ExpansionMarker(GameController::Ptr ctlr,
                                 sfg::Window::Ptr window,
                                 sfg::Button::Ptr button,
                                 MarkerType type,
                                 const Plot& plot_top)
    : mWindow{ window }, mButton{ button }, mType{ type }, mPlotTop{ plot_top }
{
    mObject = static_cast<const sf::Sprite&>(mPlotTop.GetDrawableObject());
    mObject.setColor(sf::Color::Transparent);

    using PlotType = Plot::PlotType;

    auto create_plot =
    [&plot_top = mPlotTop,
     marker = this,
     ctlr_ptr = std::weak_ptr<GameController>(ctlr),
     button = std::weak_ptr<sfg::Button>(button),
     &selected = bSelected]
    {
        if (selected) {
            assert(!ctlr_ptr.expired());
            auto ctlr = ctlr_ptr.lock();
            plot_top.SetPosition(marker->GetPosition());
            bool is_side_plot = plot_top.GetType() == PlotType::Coastal ||
                plot_top.GetType() == PlotType::Mountain;

            if (marker->GetType() == MarkerType::Upper) {
                plot_top.Move(0.f, static_cast<float>(Tile::kTileHeight));
                if (is_side_plot)
                {
                    ctlr->AddPlotToTop(plot_top);
                }
                plot_top.SetPosition(marker->GetPosition());
                ctlr->AddPlotToTop(plot_top);
            } else {
                ctlr->AddPlotToBottom(plot_top);
                plot_top.Move(0.f, static_cast<float>(Tile::kTileHeight));
                if (is_side_plot)
                {
                    ctlr->AddPlotToBottom(plot_top);
                }
            }
            marker->OnOut();
        }
        return;
    };

    mSignalSerial = connect(button, Widget::OnMouseLeftRelease, create_plot);
}

ExpansionMarker::~ExpansionMarker()
{
    // If button is expired there is no need to disconnect signal
    if (!mButton.expired()) {
        auto&& button = mButton.lock();
        button->GetSignal(Widget::OnMouseLeftRelease).Disconnect(mSignalSerial);
    }
}

void ExpansionMarker::OnHover()
{
    if (bEntered) {
        return;
    }
    bEntered = true;
    mObject.setColor(kHalfTransparent);
}

void ExpansionMarker::OnOut()
{
    if (!bEntered) {
        return;
    }
    bEntered = false;
    mObject.setColor(sf::Color::Transparent);
}

void ExpansionMarker::Select()
{
    assert(!mWindow.expired());
    if (!bSelected) {
        bSelected = true;
    }
    mWindow.lock()->Show(true);
}

} // namespace OpenLabora
