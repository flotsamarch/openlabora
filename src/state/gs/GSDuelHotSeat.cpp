#include <iostream>
#include <cassert>
#include "state/gs/GSDuelHotSeat.hpp"
#include "state/State.hpp"
#include "game/Playfield.hpp"
#include "resource/ResourceManager.hpp"

GSDuelHotSeat::GSDuelHotSeat(std::shared_ptr<State> state) : GameState{ state }
{
    auto& res_mgr = state->GetApp().GetResourceManager();
    auto build_ghost =
        std::make_unique<Location>(res_mgr, Location::LocationType::Forest);
    auto playfield = std::make_unique<Playfield>(res_mgr);

    mPlayfield = playfield.get();
    mBuildGhost = build_ghost.get();
    mBuildGhost->SetPosition(GameObject::kOutOfBounds);

    mGameObjects.push_back(std::move(playfield));
    mGameObjects.push_back(std::move(build_ghost));
}

void GSDuelHotSeat::HandleEventImpl(const sf::Event& evt)
{
    assert(!mState.expired());
    auto state = mState.lock();
    auto renderer = state->GetApp().GetRenderer();
    switch (evt.type) {
        case sf::Event::MouseMoved:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                renderer->MoveView(mMouseDeltaX, mMouseDeltaY);
            }
            break;
        }
        case sf::Event::MouseButtonReleased:
        {
            if (evt.mouseButton.button == sf::Mouse::Left && bBuildMode) {
                auto& res_mgr = state->GetApp().GetResourceManager();
                auto position = sf::Vector2i(mMouseX, mMouseY);
                auto pf_position = mPlayfield->GetSprite().getPosition();
                auto mouse_pos_local = renderer->mapPixelToCoords(position);
                mPlayfield->CreateLocationAtPoint(mouse_pos_local-pf_position,
                                                  Location::LocationType::Forest,
                                                  res_mgr);
                bBuildMode = false;
                mBuildGhost->SetPosition(GameObject::kOutOfBounds);
            }
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (evt.key.code == 'b' - 'a') {
                bBuildMode = !bBuildMode;
                if (!bBuildMode) {
                    mBuildGhost->SetPosition(GameObject::kOutOfBounds);
                }
            }
        }
        default:{}
    }

    return;
}

void GSDuelHotSeat::Update([[maybe_unused]]const float secondsSinceLastUpdate)
{
    assert(!mState.expired());
    auto renderer = mState.lock()->GetApp().GetRenderer();
    auto position = sf::Vector2i(mMouseX, mMouseY);
    auto pf_position = mPlayfield->GetSprite().getPosition();
    auto mouse_pos_local = renderer->mapPixelToCoords(position);
    auto closest_tile_coords =
        mPlayfield->SnapPointToTile(mouse_pos_local-pf_position);

    if (bBuildMode && mBuildGhost != nullptr) {
        mBuildGhost->SetPosition(closest_tile_coords);
    }
    return;
}
