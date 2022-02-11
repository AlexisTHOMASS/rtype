/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <bitset>
#include <set>

using Entity = uint16_t;
const Entity MAX_ENTITIES = UINT16_MAX;
using ComponentType = uint8_t;
const ComponentType MAX_COMPONENTS = UINT8_MAX;
const ComponentType MAX_PHASE = 16;
using Signature = std::bitset<MAX_COMPONENTS>;

class System {
    public:
        std::set<Entity> _entities;

    protected:
    private:
};

#endif /* !SYSTEM_HPP_ */
