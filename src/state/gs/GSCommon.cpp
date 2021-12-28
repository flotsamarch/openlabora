#include "state/gs/GSCommon.hpp"
#include "state/State.hpp"

namespace
{
    using LocationPtr = GSCommon::LocationPtr;
}

GSCommon::GSCommon(std::shared_ptr<State> state) : GameState{ state }
{
    auto pos = sf::Mouse::getPosition();
    mMouseX = pos.x;
    mMouseY = pos.y;
}

void GSCommon::HandleEventCommon(const sf::Event &evt,
                                 [[maybe_unused]]IRenderer& renderer)
{
    if (evt.type == sf::Event::MouseMoved) {
        mMouseDeltaX = static_cast<float>(evt.mouseMove.x - mMouseX);
        mMouseDeltaY = static_cast<float>(evt.mouseMove.y - mMouseY);
        mMouseX = evt.mouseMove.x;
        mMouseY = evt.mouseMove.y;
    }
}

void GSCommon::UpdateCommon([[maybe_unused]]const float secondsSinceLastUpdate,
                             [[maybe_unused]]IRenderer& renderer)
{
}

void GSCommon::HandleEvent(const sf::Event& evt, IRenderer& renderer)
{
    HandleEventCommon(evt, renderer);
}

void GSCommon::Update(const float secondsSinceLastUpdate,
                       IRenderer& renderer)
{
    UpdateCommon(secondsSinceLastUpdate, renderer);
}

LocationPtr GSCommon::GetOrCreateLocationOnTile(const Playfield::TileInfo& tile,
                                                Location::LocationType type)
{
    auto&& location = mLocations[tile.indices.y][tile.indices.x];

    if (location == nullptr) {
        assert(!mState.expired());
        auto&& res_mgr = mState.lock()->GetResourceManager();
        location = std::make_shared<Location>(res_mgr, type);
        location->SetPosition(static_cast<float>(tile.coord.x),
                              static_cast<float>(tile.coord.y));
        mDrawableObjects.push_back(location);
        // TODO maybe also add this to mEntities
    }

    return location;
}

LocationPtr GSCommon::ChangeLocationTypeAtPoint(const sf::Vector2f& point,
                                                const Playfield& playfield,
                                                Location::LocationType type)
{
    auto tile_info = playfield.GetTileInfoUnderPoint(point);

    if (tile_info == Playfield::kBadTile ||
        !Location::IsPlaceableOn(type, tile_info.type)) {
        return nullptr;
    }

    auto location = GetOrCreateLocationOnTile(tile_info,
                                              type);
    if (location->GetType() != type) {
        location->SetType(type);
    }
    return location;
}
