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

#include "Game/ExpansionMarker.hpp"
#include "GameState/Controllers/GameController.hpp"
#include "Resource/IResourceManager.hpp"
#include "GUI/ClickableArea.hpp"

namespace OpenLabora
{

ExpansionMarker::ExpansionMarker(MarkerType type,
                                 const Plot& plot,
                                 const Plot& plot_alt)
    : mType{ type }, mPlot{ plot },
      mPlotAlt{ plot_alt }
{
    auto spritefy = [] (const sf::Drawable& item)
    { return static_cast<const sf::Sprite&>(item); };

    mPlot.SetPosition(0.f, 0.f);
    if (mPlot.GetType() == Plot::PlotType::Central) {
        mObject = spritefy(mPlot.GetDrawableObject());
    } else {
        mPlotAlt.SetPosition(0.f, Tile::kTileHeight);
        auto top = spritefy(mPlot.GetDrawableObject());
        auto bottom = spritefy(mPlotAlt.GetDrawableObject());
        mTexture.create(mPlot.GetTileCount() * Tile::kTileWidth,
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
    mPlot.Move(offset_x, offset_y);
    mPlotAlt.Move(offset_x, offset_y);
}

void ExpansionMarker::Move(const sf::Vector2f& offset)
{
    mObject.move(offset);
    mClickableArea.Move(offset);
    mPlot.Move(offset);
    mPlotAlt.Move(offset);
}

void ExpansionMarker::SetPosition(float position_x, float position_y)
{
    auto delta_pos = mPlotAlt.GetPosition() - mPlot.GetPosition();
    mObject.setPosition(position_x, position_y);
    mClickableArea.SetPosition(position_x, position_y);
    mPlot.SetPosition(position_x, position_y);
    mPlotAlt.SetPosition(position_x + delta_pos.x,
                         position_y + delta_pos.y);
}

void ExpansionMarker::SetPosition(const sf::Vector2f& position)
{
    auto delta_pos = mPlotAlt.GetPosition() - mPlot.GetPosition();
    mObject.setPosition(position);
    mClickableArea.SetPosition(position);
    mPlot.SetPosition(position);
    mPlotAlt.SetPosition(position + delta_pos);
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
