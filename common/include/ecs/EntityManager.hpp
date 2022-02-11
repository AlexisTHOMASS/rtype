/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** EntityManager
*/

#ifndef ENTITYMANAGER_HPP_
#define ENTITYMANAGER_HPP_

#include "System.hpp"
#include "ComponentArray.hpp"
#include <array>
#include <queue>

class EntityManager {
    public:
        EntityManager()
        {
            for (Entity entity = 0; entity != MAX_ENTITIES; entity += 1) {
                _availableEntities.push(entity);
            }
        }

        ~EntityManager() = default;

        Entity createEntity()
        {
            Entity id = _availableEntities.front();

            _availableEntities.pop();
            _livingEntityCount += 1;

            return (id);
        }

        void destroyEntity(Entity entity)
        {
            _signatures[entity].reset();
            _availableEntities.push(entity);
            _livingEntityCount -= 1;
        }

        void setSignature(Entity entity, Signature signature)
        {
            _signatures[entity] = signature;
        }

        Signature getSignature(Entity entity)
        {
            return (_signatures[entity]);
        }

    protected:
    private:
        std::queue<Entity> _availableEntities;
        std::array<Signature, MAX_ENTITIES> _signatures;
        uint32_t _livingEntityCount;
};

#endif /* !ENTITYMANAGER_HPP_ */
