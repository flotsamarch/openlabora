// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <unordered_set>
#include <memory>
#include <concepts>
#include <SFML/Graphics/Drawable.hpp>
#include "Common.hpp"
#include "ECS/Entity.hpp"
#include "Game/Playfield.hpp"
// #include "Game/Location.hpp"

namespace OpenLabora
{

class Model final
{
    // Entities are unique and we want to find them quickly by id
    using EntityContainer = std::unordered_map<uid::Uid, Entity>;

    EntityContainer mEntities;
    model::DrawableContainer mDrawableObjects;

    bool bPaused{ false };
    static constexpr uint32_t kMaxPlayers = 4;
    std::array<std::shared_ptr<Playfield>, kMaxPlayers> mPlayfields;

    sf::Vector2f mWorldMousePosition{};

public:
    enum PlayerAffiliation { Player1, Player2, Player3, Player4 };

    using Ptr = std::shared_ptr<Model>;
    using PtrConst = std::shared_ptr<const Model>;

    using EntityIter = EntityContainer::iterator;
    using EntityIterConst = EntityContainer::const_iterator;
    using EntityRange = RangeWrapper<EntityIter>;
    using EntityRangeConst = RangeWrapper<EntityIterConst>;

public:
    bool IsPaused() const noexcept
    { return bPaused; }

    void SetPaused(bool value)
    { bPaused = value; }

    void ResetEntities() noexcept
    { mEntities.clear(); }

    EntityRange GetEntities()
    { return { mEntities.begin(), mEntities.end() }; }

    EntityRangeConst GetEntities() const
    { return { mEntities.cbegin(), mEntities.cend() }; }

    template<class T>
    uid::Uid AddEntity(std::shared_ptr<T> object)
    {
        auto&& entity = Entity{ object };
        const auto id = entity.GetId();
        mEntities.emplace(id, std::move(entity)); // Maybe check for success
        return id;
    }

    void RemoveEntity(const uid::Uid& id)
    {
        auto it = mEntities.find(id);
        if (it != mEntities.end()) {
            mEntities.erase(it);
        }
    }

    void RemoveEntityBulk(std::span<uid::Uid> ids)
    {
        auto remaining_ids = std::vector<uid::Uid>{ ids.begin(), ids.end() };

        auto pred = [&ids = remaining_ids] (auto&& ent)
        {
            const auto& it = std::find(ids.begin(), ids.end(), ent.GetId());
            const bool result = it != ids.end();

            if (result) {
                ids.erase(it);
            }

            return result;
        };

        auto end = mEntities.end();
        for (auto it = mEntities.begin(); it != end;) {
            auto tmp = it++;
            if (pred(tmp->second)) {
                mEntities.erase(tmp);
            }
        }
    }

    model::DrawableRangeConst GetDrawableObjects() const noexcept
    { return { mDrawableObjects.cbegin(), mDrawableObjects.cend() }; }

    void ClearDrawableObjects() noexcept
    { mDrawableObjects.clear(); }

    template<model::Drawable T>
    void AddDrawableObject(T&& drawable)
    {
        using Type = std::remove_cvref_t<T>;
        auto&& ptr = std::make_unique<Type>(std::forward<T>(drawable));
        mDrawableObjects.emplace_back(std::move(ptr));
    }

    std::shared_ptr<Playfield>& GetPlayfield(Model::PlayerAffiliation player)
    { return mPlayfields.at(player); }

    std::shared_ptr<const Playfield>
    GetPlayfield(Model::PlayerAffiliation player) const
    { return const_pointer_cast<const Playfield>(mPlayfields.at(player)); }

    std::span<std::shared_ptr<Playfield>> GetPlayfields()
    { return mPlayfields; }

    const sf::Vector2f& GetWorldMousePosition() const
    { return mWorldMousePosition; }

    void SetWorldMousePosition(const sf::Vector2f& position)
    { mWorldMousePosition = position; }
};

} // namespace OpenLabora

#endif // MODEL_HPP_
