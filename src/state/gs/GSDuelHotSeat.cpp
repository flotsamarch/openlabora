#include <iostream>
#include <cassert>
#include "state/gs/GSDuelHotSeat.hpp"
#include "state/State.hpp"
#include "resource/ResourceManager.hpp"

GSDuelHotSeat::GSDuelHotSeat(std::shared_ptr<State> state) : GameState{ state }
{
    auto&& res_mgr = state->GetApp().GetResourceManager();

    mPlayfield = std::make_shared<Playfield>(res_mgr);
    mBuildGhost = std::make_shared<Location>(res_mgr, Location::LocationType::Forest);
    mBuildGhost->SetPosition(GameObject::kOutOfBounds);

    mGameObjects.push_back(mPlayfield);
    mGameObjects.push_back(mBuildGhost);
}

void GSDuelHotSeat::HandleEventImpl(const sf::Event& evt)
{
    if (bPaused) {
        return;
    }

    assert(!mState.expired());
    auto state = mState.lock();
    auto&& renderer = state->GetApp().GetRenderer();
    switch (evt.type) {
        case sf::Event::MouseMoved:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                renderer.MoveView(mMouseDeltaX, mMouseDeltaY);
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (evt.mouseButton.button == sf::Mouse::Left && bBuildModeEnabled) {
                auto&& res_mgr = state->GetApp().GetResourceManager();
                auto position = sf::Vector2i(mMouseX, mMouseY);
                auto pf_position = mPlayfield->GetSprite().getPosition();
                auto mouse_pos_pf = renderer.mapPixelToCoords(position);
                mPlayfield->ChangeLocationTypeAtPoint(mouse_pos_pf-pf_position,
                                                      mBuildGhost->GetType());
                bBuildModeEnabled = false;
                mBuildGhost->SetPosition(GameObject::kOutOfBounds);
            }
            break;
        }
        // case sf::Event::KeyPressed:
        // {}
        default: {}
    }

}

void GSDuelHotSeat::Update([[maybe_unused]]const float secondsSinceLastUpdate)
{
    if (bPaused) {
        return;
    }

    assert(!mState.expired());
    auto&& renderer = mState.lock()->GetApp().GetRenderer();
    auto position = sf::Vector2i(mMouseX, mMouseY);
    auto pf_position = mPlayfield->GetSprite().getPosition();
    auto mouse_pos_local = renderer.mapPixelToCoords(position);
    auto closest_tile_coords =
        mPlayfield->SnapPointToTile(mouse_pos_local-pf_position);

    if (bBuildModeEnabled && mBuildGhost != nullptr) {
        mBuildGhost->SetPosition(closest_tile_coords);
    }
    return;
}


void GSDuelHotSeat::EnableBuildMode(Location::LocationType type)
{
    mBuildGhost->SetType(type);
    bBuildModeEnabled = true;
};
