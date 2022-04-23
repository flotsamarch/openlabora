#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <memory>
#include <SFML/Window/Event.hpp>
#include "Game/Playfield.hpp"

namespace OpenLabora
{

class GameController;

class Entity final
{
    struct IEntity
    {
        virtual ~IEntity() = default;

        virtual void Update(std::shared_ptr<GameController>,
                            float update_delta_seconds) = 0;

        // @return true if event was handled and shouldn't be propagated further
        virtual bool HandleEvent(std::shared_ptr<GameController>,
                                 const sf::Event&) = 0;
    };

    template<class T>
    struct EntityObject : IEntity
    {
        std::shared_ptr<T> mEntity;
        EntityObject(std::shared_ptr<T> entity)
            : mEntity{ entity } {};

        void Update(std::shared_ptr<GameController> controller,
                    float update_delta_seconds) override
        { entityUpdate(mEntity, update_delta_seconds, controller); };

        bool HandleEvent(std::shared_ptr<GameController> controller,
                         const sf::Event& event) override
        { return entityHandleEvent(mEntity, controller, event); };
    };

    std::unique_ptr<IEntity> mSelf;

public:
    template<class T>
    Entity(std::shared_ptr<T> entity)
        : mSelf{ std::make_unique<EntityObject<T>>(entity) } {};

    friend void entityUpdate(Entity& entity,
                             float update_delta_seconds,
                             std::shared_ptr<GameController> controller)
    { entity.mSelf->Update(controller, update_delta_seconds); };

    friend bool entityHandleEvent(Entity& entity,
                                  std::shared_ptr<GameController> controller,
                                  const sf::Event& event)
    { return entity.mSelf->HandleEvent(controller, event); };
};

} // namespace OpenLabora

#endif // ENTITY_HPP_
