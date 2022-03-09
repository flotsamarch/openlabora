#include "Game/ExpansionMarker.hpp"
#include "AppState/AppStateManager.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "resource/IResourceManager.hpp"
#include "GUI/Utility.hpp"
#include "GUI/ClickableArea.hpp"

namespace OpenLabora
{

ExpansionMarker::ExpansionMarker(MarkerType type,
                                 const Plot& plot_top,
                                 OptionalPlot plot_bottom)
    : mType{ type }, mPlotTop{ plot_top },
      mPlotBottom{ plot_bottom }
{
    auto spritefy = [] (const sf::Drawable& item)
    { return static_cast<const sf::Sprite&>(item); };

    mPlotTop.SetPosition(0.f, 0.f);
    if (mPlotBottom == std::nullopt) {
        mObject = spritefy(mPlotTop.GetDrawableObject());
    } else {
        mPlotBottom->SetPosition(0.f, Tile::kTileHeight);
        auto top = spritefy(mPlotTop.GetDrawableObject());
        auto bottom = spritefy(mPlotBottom->GetDrawableObject());
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
    auto&& sprite = mObject;
    auto on_out = [&sprite] {sprite.setColor(sf::Color::Transparent);};
    on_out();

    SetOnOutDelegate(on_out);
    SetOnHoverDelegate([&sprite] {sprite.setColor(kHalfTransparent);});
}

void ExpansionMarker::Move(float offset_x, float offset_y)
{
    mObject.move(offset_x, offset_y);
    mClickableArea.Move(offset_x, offset_y);
    mPlotTop.Move(offset_x, offset_y);
    if (mPlotBottom.has_value()) {
        mPlotBottom->Move(offset_x, offset_y);
    }
}

void ExpansionMarker::Move(const sf::Vector2f& offset)
{
    mObject.move(offset);
    mClickableArea.Move(offset);
    mPlotTop.Move(offset);
    if (mPlotBottom.has_value()) {
        mPlotBottom->Move(offset);
    }
}

void ExpansionMarker::SetPosition(float position_x, float position_y)
{
    mObject.setPosition(position_x, position_y);
    mClickableArea.SetPosition(position_x, position_y);
    if (mPlotBottom.has_value()) {
        auto delta_pos = mPlotBottom->GetPosition() - mPlotTop.GetPosition();
        mPlotBottom->SetPosition(position_x + delta_pos.x,
                                 position_y + delta_pos.y);
    }
    mPlotTop.SetPosition(position_x, position_y);
}

void ExpansionMarker::SetPosition(const sf::Vector2f& position)
{
    mObject.setPosition(position);
    mClickableArea.SetPosition(position);
    if (mPlotBottom.has_value()) {
        auto delta_pos = mPlotBottom->GetPosition() - mPlotTop.GetPosition();
        mPlotBottom->SetPosition(position + delta_pos);
    }
    mPlotTop.SetPosition(position);
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
