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
    mBuildGhost = CreateEntity<Location>(res_mgr, Location::LocationType::Forest);

    mBuildGhost->SetPosition(Entity::kOutOfBounds);

    auto size = sf::Vector2f(500.f, 500.f);

    auto marker = CreateEntity<LandPurchaseMarker>(size);
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

            for (auto&& item : mSelectableObjects) {
                if (item.expired()) {
                    continue;
                }

                auto ptr = item.lock();
                assert(ptr != nullptr);
                if (ptr->IsUnderPoint(mouse_pos_local)) {
                    ptr->OnHover();
                } else {
                    ptr->OnOut();
                }
            }

            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (evt.mouseButton.button == sf::Mouse::Left && bBuildModeEnabled) {
                auto pf_position = mPlayfields[Player1]->GetPosition();

                ChangeLocationTypeAtPoint(mouse_pos_local - pf_position,
                                          *mPlayfields[Player1],
                                          mBuildGhost->GetType());

                bBuildModeEnabled = false;
                mBuildGhost->SetPosition(Entity::kOutOfBounds);
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
    if (tile_info != Playfield::kBadTile &&
        bBuildModeEnabled && mBuildGhost != nullptr) {
        mBuildGhost->SetPosition(tile_info.coord);
    } else if (mBuildGhost->GetPosition() != Entity::kOutOfBounds) {
        mBuildGhost->SetPosition(Entity::kOutOfBounds);
    }

    return;
}

void GSDuel::EnableBuildMode(Location::LocationType type)
{
    mBuildGhost->SetType(type);
    bBuildModeEnabled = true;
};
