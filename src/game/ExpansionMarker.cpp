#include "Game/ExpansionMarker.hpp"
#include "AppState/AppStateManager.hpp"
#include "resource/IResourceManager.hpp"
#include "Game/Playfield.hpp"
#include "GUI/Utility.hpp"

namespace OpenLabora
{

namespace
{
    using Widget = sfg::Widget;
}

ExpansionMarker::ExpansionMarker(const Plot& plot,
                                 MarkerType type,
                                 std::shared_ptr<Playfield> playfield,
                                 std::shared_ptr<sfg::Window> window,
                                 std::shared_ptr<sfg::Button> button)
    : mPlot{ plot }, mType{ type }, mWindow{ window }, mButton{ button }
{
    mObject = static_cast<const sf::Sprite&>(mPlot.GetDrawableObject());
    mObject.setColor(sf::Color::Transparent);

    using PlotType = Plot::PlotType;

    auto create_plot =
    [&plot = mPlot,
     marker = this,
     playfield = std::weak_ptr<Playfield>(playfield),
     button = std::weak_ptr<sfg::Button>(button),
     &selected = bSelected]
    {
        if (selected) {
            assert(!playfield.expired());
            auto pf = playfield.lock();
            plot.SetPosition(marker->mObject.getPosition());
            if (marker->GetType() == MarkerType::Upper) {
                pf->PushPlotFront(plot);
            } else {
                pf->PushPlotBack(plot);
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
