/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** Coordinator
*/

#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "System.hpp"
#include "SystemManager.hpp"
#include <memory>

class Coordinator
{
    public:
        Coordinator()
        {
            _componentManager = std::make_unique<ComponentManager>();
            _entityManager = std::make_unique<EntityManager>();
            _systemManager = std::make_unique<SystemManager>();
            _score = {0, 0};
        }

        ~Coordinator() = default;

        Entity createEntity()
        {
            return _entityManager->createEntity();
        }

        void destroyEntity(Entity entity)
        {
            _entityManager->destroyEntity(entity);
            // _componentManager->entityDestroyed(entity);
            _systemManager->entityDestroyed(entity);
        }

        template <typename T>
        void addComponent(Entity entity, T component)
        {
            _componentManager->addComponent<T>(entity, component);
            auto signature = _entityManager->getSignature(entity);

            signature.set(_componentManager->getComponentType<T>(), true);
            _entityManager->setSignature(entity, signature);
            _systemManager->entitySignatureChanged(entity, signature);
        }

        template <typename T>
        void removeComponent(Entity entity)
        {
            _componentManager->removeComponent<T>(entity);
            auto signature = _entityManager->getSignature(entity);
            signature.set(_componentManager->getComponentType<T>(), false);
            _entityManager->setSignature(entity, signature);
            _systemManager->entitySignatureChanged(entity, signature);
        }

        template <typename T>
        void registerComponent()
        {
            _componentManager->registerComponent<T>();
        }

        template <typename T>
        T &getComponent(Entity entity)
        {
            return _componentManager->getComponent<T>(entity);
        }

        template <typename T>
        ComponentType getComponentType()
        {
            return _componentManager->getComponentType<T>();
        }

        template <typename T>
        std::shared_ptr<T> registerSystem()
        {
            return _systemManager->registerSystem<T>();
        }

        template <typename T>
        void setSystemSignature(Signature signature)
        {
            _systemManager->setSignature<T>(signature);
        }

        Signature getSignature(Entity entity)
        {
            return (_entityManager->getSignature(entity));
        }

        std::bitset<MAX_PHASE> phase;
        Entity _player;
        std::pair<Entity, float> _score;
    private:
        std::unique_ptr<ComponentManager> _componentManager;
        std::unique_ptr<EntityManager> _entityManager;
        std::unique_ptr<SystemManager> _systemManager;
};

#endif /* !COORDINATOR_HPP_ */