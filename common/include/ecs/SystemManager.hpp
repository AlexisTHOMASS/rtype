/*
** EPITECH PROJECT, 2021
** Visual Studio Live Share (Workspace)
** File description:
** SystemManager
*/

#ifndef SYSTEM_MANAGER__HPP
#define SYSTEM_MANAGER__HPP

#include "System.hpp"
#include <memory>
#include <unordered_map>

class SystemManager
{
    public:

        template<typename T>
        std::shared_ptr<T> registerSystem()
        {
            const char* typeName = typeid(T).name();

            std::shared_ptr<T> system = std::make_shared<T>();
            _systems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void setSignature(Signature signature)
        {
            const char* typeName = typeid(T).name();
            _signatures.insert({typeName, signature});
        }

        void entityDestroyed(Entity entity)
        {
            for (auto const& pair : _systems) {
                auto const& system = pair.second;
                system->_entities.erase(entity);
            }
        }

        void entitySignatureChanged(Entity entity, Signature entitySignature)
        {
            for (auto const& pair : _systems) {
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemSignature = _signatures[type];

                if ((entitySignature & systemSignature) == systemSignature)
                    system->_entities.insert(entity);
                else
                    system->_entities.erase(entity);
            }
        }

    private:
        std::unordered_map<const char*, Signature> _signatures;
        std::unordered_map<const char*, std::shared_ptr<System>> _systems;
};

#endif