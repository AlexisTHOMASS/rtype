/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** KillEnemy
*/

#include "KillEnemy.hpp"
#include "Ship.hpp"
#include "Motion.hpp"
#include <vector>
#include <iostream>

void KillEnemy::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
}

std::vector<Entity> KillEnemy::update()
{
    std::vector<Entity> killed;
    for (auto const& entity : _entities) {
        auto &ship = _coordinator->getComponent<Ship>(entity);

        if (ship.hp <= 0) {
            auto &motion = _coordinator->getComponent<Motion>(entity);
            if (ship.isFreindly)
                motion.velocity.x = -550;
            else {
                motion.velocity.x = 300;
            }
            motion.rotation = 360;
            killed.push_back(entity);
        }
    }
    return killed;
}

