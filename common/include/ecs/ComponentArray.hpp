/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** ComponentArray
*/

#ifndef COMPONENTARRAY_HPP_
#define COMPONENTARRAY_HPP_

#include "System.hpp"
#include "IComponentArray.hpp"
#include <array>
#include <unordered_map>

template<class T>
class ComponentArray : public IComponentArray {
    public:

        void insertData(Entity entity, T component)
        {
            size_t newIndex = _size;
            _entityToIndexMap[entity] = newIndex;
            _indexToEntityMap[newIndex] = entity;
            _componentArray[newIndex] = component;
            _size += 1;
            if (_size >= MAX_ENTITIES - 1)
                _size /= 2;
        }

        void removeData(Entity entity)
        {
            size_t indexOfRemovedEntity = _entityToIndexMap[entity];
            size_t indexOfLastElement = _size - 1;
            Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];

            _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];
            _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
            _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

            _entityToIndexMap.erase(entity);
            _indexToEntityMap.erase(indexOfLastElement);

            _size -= 1;
        }

        T& getData(Entity entity)
        {
            return (_componentArray[_entityToIndexMap[entity]]);
        }

        void entityDestroyed(Entity entity) override
        {
            if (_entityToIndexMap.find(entity) != _entityToIndexMap.end()) {
                removeData(entity);
            }
        }

    protected:
    private:
        std::array<T, MAX_ENTITIES> _componentArray;
        std::unordered_map<Entity, size_t> _entityToIndexMap;
        std::unordered_map<size_t, Entity> _indexToEntityMap;
        size_t _size;
};

#endif /* !COMPONENTARRAY_HPP_ */
