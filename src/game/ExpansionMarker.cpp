#include "Game/ExpansionMarker.hpp"
#include "AppState/AppStateManager.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "resource/IResourceManager.hpp"
#include "GUI/Utility.hpp"
#include "GUI/ClickableArea.hpp"

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
                                 OptionalPlot plot_bottom)
    : mWindow{ window }, mButton{ button }, mType{ type }, mPlotTop{ plot_top },
      mPlotBottom{ plot_bottom }
{
    if (mPlotBottom == std::nullopt) {
        mObject = static_cast<const sf::Sprite&>(mPlotTop.GetDrawableObject());
    } else {
        auto spritefy = [] (const sf::Drawable& item)
        { return static_cast<const sf::Sprite&>(item); };

        sf::Sprite top = spritefy(mPlotTop.GetDrawableObject());
        sf::Sprite bottom = spritefy(mPlotBottom->GetDrawableObject());
        top.setPosition(0.f, 0.f);
        bottom.setPosition(0.f, Tile::kTileHeight);
        mTexture.create(mPlotTop.GetTileCount() * Tile::kTileWidth,
                        2 * Tile::kTileHeight);
        mTexture.clear();
        mTexture.draw(top);
        mTexture.draw(bottom);
        mTexture.display();
        mObject.setTexture(mTexture.getTexture(), true);
    }

    const auto bounds = mObject.getLocalBounds();
    const bool is_lower = type == MarkerType::Lower;
    if (type == MarkerType::Upper || is_lower) {
        const auto offset = is_lower ? kMarkerOverlapFactor : 0.f;
        const auto offset_vec = sf::Vector2f{ 0.f, bounds.height * offset };
        const auto height = bounds.height * (1 - kMarkerOverlapFactor);
        const auto rect_size = sf::Vector2f{ bounds.width, height };

        mClickableArea = RectangleArea{offset_vec, rect_size};
    }
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

void ExpansionMarker::Move(float offset_x, float offset_y)
{
    mObject.move(offset_x, offset_y);
    mClickableArea.Move(offset_x, offset_y);
}

void ExpansionMarker::Move(const sf::Vector2f& offset)
{
    mObject.move(offset);
    mClickableArea.Move(offset);
}

void ExpansionMarker::SetPosition(float position_x, float position_y)
{
    mObject.setPosition(position_x, position_y);
    mClickableArea.SetPosition(position_x, position_y);
}

void ExpansionMarker::SetPosition(const sf::Vector2f& position)
{
    mObject.setPosition(position);
    mClickableArea.SetPosition(position);
}

void ExpansionMarker::ResetClickableArea()
{
    const auto bounds = mObject.getLocalBounds();
    const auto rect_size = sf::Vector2f{ bounds.width, bounds.height };
    mClickableArea = RectangleArea{ sf::Vector2f(), rect_size };
    mClickableArea.SetPosition(GetPosition());
}

void ExpansionMarker::SetClickableArea(const sf::Vector2f &offset,
                                       const sf::Vector2f &rect_size)
{
    mClickableArea = RectangleArea{ offset, rect_size };
    mClickableArea.SetPosition(GetPosition());
}


} // namespace OpenLabora
