/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** ComponentManager
*/

#ifndef COMPONENTMANAGER_HPP_
#define COMPONENTMANAGER_HPP_

#include "System.hpp"
#include "ComponentArray.hpp"
#include <unordered_map>
#include <memory>


class ComponentManager {
    public:
        template<typename T>
        void registerComponent()
        {
            const char* typeName = typeid(T).name();

            _componentTypes.insert({typeName, _nextComponentType});
            _componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

            _nextComponentType += 1;
        }

        template<typename T>
        ComponentType getComponentType()
        {
            const char* typeName = typeid(T).name();

            return _componentTypes[typeName];
        }

        template<typename T>
        void addComponent(Entity entity, T component)
        {
            getComponentArray<T>()->insertData(entity, component);
        }

        template<typename T>
        void removeComponent(Entity entity)
        {
            getComponentArray<T>()->removeData(entity);
        }

        template<typename T>
        T& getComponent(Entity entity)
        {
            return getComponentArray<T>()->getData(entity);
        }

        void entityDestroyed(Entity entity)
        {
            for (auto const& pair : _componentArrays) {
                auto const& component = pair.second;

                component->entityDestroyed(entity);
            }
        }

    private:
        template<typename T>
        std::shared_ptr<ComponentArray<T>> getComponentArray()
        {
            const char* typeName = typeid(T).name();
            return std::static_pointer_cast<ComponentArray<T>>(_componentArrays[typeName]);
        }

    private:
    std::unordered_map<const char*, ComponentType> _componentTypes;
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> _componentArrays;
    ComponentType _nextComponentType;

};

#endif /* !COMPONENTMANAGER_HPP_ */
