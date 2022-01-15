#include <iostream>
#include <cassert>
#include "state/gs/GSDuel.hpp"
#include "state/State.hpp"
#include "resource/ResourceManager.hpp"
#include "game/LandPurchaseMarker.hpp"

GSDuel::GSDuel(std::shared_ptr<State> state) : GSCommon { state }
{
    auto&& res_mgr = state->GetResourceManager();

    mPlayfields[Player1] = CreateEntity<Playfield>(res_mgr);
    // mBuildGhost = CreateEntity<Location>(res_mgr, Location::LocationType::Forest);

    // mBuildGhost->SetPosition(Entity::kOutOfBounds);
    auto [plot_top, plot_bottom] =
        mPlayfields[Player1]->GetLandTopAndBottomEdges(Plot::PlotType::Central);

    auto marker_pos = sf::Vector2f{ mPlayfields[Player1]->GetPosition().x,
                                    plot_top - Tile::kTileHeight };
    marker_pos.x +=
        Tile::kTileWidth * Plot::GetPlotWidthTileCount(Plot::PlotType::Coastal);

    auto marker_central_top = CreateEntity<LandPurchaseMarker>(
        Plot{Plot::kCentralPlotTop, res_mgr}, true);

    marker_central_top->SetPosition(marker_pos);

    marker_pos.y = plot_bottom;

    auto marker_central_bottom = CreateEntity<LandPurchaseMarker>(
        Plot{Plot::kCentralPlotBottom, res_mgr}, false);

    marker_central_bottom->SetPosition(marker_pos);
}

void GSDuel::HandleEvent(const sf::Event& evt, IRenderer& renderer)
{
    HandleEventCommon(evt, renderer);

    if (bPaused) {
        return;
    }

    assert(!mState.expired());
    auto state = mState.lock();
    auto position = sf::Vector2i{ mMouseX, mMouseY };
    auto mouse_pos_local = renderer.mapPixelToCoords(position);

    switch (evt.type) {
        case sf::Event::MouseMoved:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                renderer.MoveView(mMouseDeltaX, mMouseDeltaY);
            }

            if (bMouseCapturedByGui) {
                break;
            }

            for (auto&& item : mSelectableObjects) {
                if (item.expired()) {
                    continue;
                }

                auto&& entity = static_cast<SelectableEntity&>(*item.lock());
                if (entity.IsUnderPoint(mouse_pos_local)) {
                    mEntityUnderCursor = item;
                    entity.OnHover();
                } else {
                    if (!mEntityUnderCursor.expired()
                        && mEntityUnderCursor.lock() == item.lock())
                    {
                        mEntityUnderCursor.lock() = nullptr;
                    }
                    entity.OnOut();
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (bMouseCapturedByGui) {
                break;
            }

            if (evt.mouseButton.button == sf::Mouse::Left
                && !mEntityUnderCursor.expired()
                && mEntityUnderCursor.lock() != nullptr)
            {
                mEntityUnderCursor.lock()->Select(mState.lock());
            }

            if (evt.mouseButton.button == sf::Mouse::Left && bBuildModeEnabled) {
                auto pf_position = mPlayfields[Player1]->GetPosition();

                // ChangeLocationTypeAtPoint(mouse_pos_local - pf_position,
                                          // *mPlayfields[Player1],
                                          // mBuildGhost->GetType());

                bBuildModeEnabled = false;
                // mBuildGhost->SetPosition(Entity::kOutOfBounds);
            }
            break;
        }
        default: {}
    }

}

void GSDuel::Update(const float secondsSinceLastUpdate,
    IRenderer& renderer)
{
    UpdateCommon(secondsSinceLastUpdate, renderer);
    if (bPaused) {
        return;
    }

    assert(!mState.expired());
    auto position = sf::Vector2i(mMouseX, mMouseY);
    auto pf_position = mPlayfields[Player1]->GetPosition();
    auto mouse_pos_local = renderer.mapPixelToCoords(position);
    auto tile_info = mPlayfields[Player1]->
        GetTileInfoUnderPoint(mouse_pos_local-pf_position);
    #if 0
    if (tile_info != Tile::kBadTile &&
        bBuildModeEnabled && mBuildGhost != nullptr) {
        mBuildGhost->SetPosition(tile_info.coord);
    } else if (mBuildGhost->GetPosition() != Entity::kOutOfBounds) {
        mBuildGhost->SetPosition(Entity::kOutOfBounds);
    }
    #endif
    return;
}

void GSDuel::EnableBuildMode(Location::LocationType type)
{
    // mBuildGhost->SetType(type);
    bBuildModeEnabled = true;
};
