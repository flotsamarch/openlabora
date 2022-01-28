#include "Game/ExpansionMarker.hpp"
#include "AppState/AppStateManager.hpp"
#include "resource/IResourceManager.hpp"
#include "Game/Playfield.hpp"

namespace OpenLabora
{

ExpansionMarker::ExpansionMarker(const Plot& plot,
                                 MarkerType type,
                                 std::shared_ptr<Playfield> playfield,
                                 std::shared_ptr<sfg::Window> window,
                                 std::shared_ptr<sfg::Button> button)
    : mPlot{ plot }, mType{ type }, mWindow{ window }
{
    mObject = static_cast<const sf::Sprite&>(mPlot.GetDrawableObject());
    mObject.setColor(sf::Color::Transparent);

    using PlotType = Plot::PlotType;
    using Widget = sfg::Widget;

    auto create_plot = [&plot = mPlot,
                        marker_type = mType,
                        &marker_obj = mObject,
                        playfield = std::weak_ptr<Playfield>(playfield),
                        button = std::weak_ptr<sfg::Button>(button),
                        window = mWindow,
                        &selected = bSelected]
    {
        if (selected) {
            assert(!window.expired());
            assert(!playfield.expired());
            auto pf = playfield.lock();
            plot.SetPosition(marker_obj.getPosition());
            if (marker_type == MarkerType::Upper) {
                pf->PushPlotFront(plot);
            } else {
                pf->PushPlotBack(plot);
            }
            window.lock()->Show(false);
        }
        return;
    };

    button->GetSignal(Widget::OnMouseLeftRelease).Connect(create_plot);
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
