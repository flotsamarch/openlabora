#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <vector>
#include <memory>
#include <bitset>
#include <span>
#include <SFML/Window/Event.hpp>
#include "Game/IEntity.hpp"
#include "Game/IDrawable.hpp"
#include "Game/ISelectable.hpp"
#include "Game/Location.hpp"
#include "Game/ExpansionMarker.hpp"

namespace OpenLabora
{

template<class TEntity>
concept CEntity = std::derived_from<TEntity, IEntity>;

class Model final
{
public:
    enum PlayerAffiliation { Player1, Player2, Player3, Player4 };
    static constexpr uint32_t kMaxPlayers = 4;

    using CDrawableSpan = std::span<const std::shared_ptr<const IDrawable>>;
    using CEntitySpan = std::span<const std::shared_ptr<const IEntity>>;
    using CSelectableSpan = std::span<const std::shared_ptr<const ISelectable>>;
private:
    using DrawableSpan = std::span<std::shared_ptr<IDrawable>>;
    using EntitySpan = std::span<std::shared_ptr<IEntity>>;
    using SelectableSpan = std::span<std::shared_ptr<ISelectable>>;

    std::vector<std::shared_ptr<IEntity>> mEntities;
    std::vector<std::shared_ptr<IDrawable>> mDrawableEntities;
    std::vector<std::shared_ptr<ISelectable>> mSelectableEntities;

    sf::View mMainView;
    sf::Vector2u mWindowSize;
    std::bitset<sf::Event::Count> mIgnoredEvents;

    bool bPaused{ false };

    std::array<std::shared_ptr<Playfield>, kMaxPlayers> mPlayfields;

public:
    Model(const sf::Vector2u& window_size) : mWindowSize{ window_size } {}

    template<CEntity TEntity, class... Args>
    std::shared_ptr<TEntity> CreateEntity(Args&&... args);

    template<CEntity TEntity>
    void RemoveEntity(std::shared_ptr<TEntity> entity);

    const sf::View& GetMainView() const noexcept
    { return mMainView; }

    void MoveMainView(const sf::Vector2f offset)
    { mMainView.move(offset); }

    void ResetMainView(const sf::FloatRect& viewport)
    { mMainView.reset(viewport); }

    const sf::Vector2u& GetWindowSize() const noexcept
    { return mWindowSize; }

    void SetWindowSize(const sf::Vector2u& window_size)
    { mWindowSize = window_size; }

    const bool IsEventIgnored(sf::Event::EventType type) const
    { return mIgnoredEvents.test(type); }

    void IgnoreNextEvent(sf::Event::EventType type, bool value = true)
    { mIgnoredEvents.set(type, value); }

    bool IsPaused() const noexcept
    { return bPaused; }

    void SetPaused(bool value)
    { bPaused = value; }

    void ResetEntities() noexcept
    { mEntities.clear(); mSelectableEntities.clear(); mDrawableEntities.clear();}

    DrawableSpan GetDrawableEntities() noexcept
    { return mDrawableEntities; }

    EntitySpan GetEntities() noexcept
    { return mEntities; }

    SelectableSpan GetSelectableEntities() noexcept
    { return mSelectableEntities; }

    CDrawableSpan GetDrawableEntities() const noexcept;

    CEntitySpan GetEntities() const noexcept;

    CSelectableSpan GetSelectableEntities() const noexcept;

    std::shared_ptr<Playfield>& GetPlayfield(Model::PlayerAffiliation player)
    { return mPlayfields.at(player); }

    std::shared_ptr<const Playfield>
    GetPlayfield(Model::PlayerAffiliation player) const
    { return const_pointer_cast<const Playfield>(mPlayfields.at(player)); }

    std::span<std::shared_ptr<Playfield>> GetPlayfields()
    { return mPlayfields; }
};

template<CEntity TEntity, class... Args>
std::shared_ptr<TEntity> Model::CreateEntity(Args&&... args)
{
    auto entity = std::make_shared<TEntity>(std::forward<Args>(args)...);
    mEntities.push_back(entity);

    if constexpr(std::derived_from<TEntity, IDrawable>) {
        auto drwbl_entity = std::static_pointer_cast<IDrawable>(entity);
        mDrawableEntities.push_back(drwbl_entity);
    }

    if constexpr(std::derived_from<TEntity, ISelectable>) {
        auto sel_entity = std::static_pointer_cast<ISelectable>(entity);
        mSelectableEntities.push_back(sel_entity);
    }

    return entity;
}

template<CEntity TEntity>
void Model::RemoveEntity(std::shared_ptr<TEntity> entity)
{
    {
        auto to_remove = std::ranges::find(mEntities, entity);
        mEntities.erase(to_remove);
    }

    if constexpr(std::derived_from<TEntity, IDrawable>) {
        auto sel_entity = std::static_pointer_cast<IDrawable>(entity);
        auto to_remove = std::ranges::find(mDrawableEntities, entity);
        mDrawableEntities.erase(to_remove);
    }

    if constexpr(std::derived_from<TEntity, ISelectable>) {
        auto sel_entity = std::static_pointer_cast<ISelectable>(entity);
        auto to_remove = std::ranges::find(mSelectableEntities, entity);
        mSelectableEntities.erase(to_remove);
    }
}

inline Model::CDrawableSpan Model::GetDrawableEntities() const noexcept
{
    // Vectors in model can't hold ptrs to const since entites have to be mutable
    // When any class has pointer to const Model it implies read-only access
    // Enforce constness with cast to return read-only span
    auto data = const_cast<IDrawable::Ptr*>(mDrawableEntities.data());
    if (data == nullptr || *data == nullptr) {
        return {};
    }
    auto cdata = reinterpret_cast<IDrawable::CPtr*>(data);
    return std::span(cdata, mDrawableEntities.size());
}

inline Model::CEntitySpan Model::GetEntities() const noexcept
{
    // Enforce constness with cast to return read-only span
    auto data = const_cast<IEntity::Ptr*>(mEntities.data());
    if (data == nullptr || *data == nullptr) {
        return {};
    }
    auto cdata = reinterpret_cast<IEntity::CPtr*>(data);
    return std::span(cdata, mEntities.size());
}

inline Model::CSelectableSpan Model::GetSelectableEntities() const noexcept
{
    // Enforce constness with cast to return read-only span
    auto data = const_cast<ISelectable::Ptr*>(mSelectableEntities.data());
    if (data == nullptr || *data == nullptr) {
        return {};
    }
    auto cdata = reinterpret_cast<ISelectable::CPtr*>(data);
    return std::span(cdata, mSelectableEntities.size());
}

} // namespace OpenLabora

#endif // MODEL_HPP_
