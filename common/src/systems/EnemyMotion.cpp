/*
** EPITECH PROJECT, 2021
** B-CPP-501-PAR-5-1-rtype-quentin.daville
** File description:
** EnemyMotion
*/

#include "EnemyMotion.hpp"
#include "Motion.hpp"
#include "Ship.hpp"
#include "Sprite.hpp"
#include "Random.hpp"

extern sf::Vector2f windowScale;

void EnemyMotion::init(Coordinator *coordinator)
{
    _coordinator = coordinator;
}

std::vector<Entity> EnemyMotion::update()
{
    static Random<int> accelerationRand(10, 100);
    static Random<int> direction(0, 1);
    std::vector<Entity> updateEnemy;

    for (auto const& entity : _entities) {
        auto &enemy = _coordinator->getComponent<Ship>(entity);
        if (enemy.isFreindly)
            continue;
        auto &sprite = _coordinator->getComponent<Sprite>(entity);
        auto &motion = _coordinator->getComponent<Motion>(entity);
        sf::Vector2f pos = sprite.sprite.getPosition();

        if (!enemy.stop && pos.x * windowScale.x < enemy.xPos * windowScale.x) {
            motion.acceleration.x = 0;
            motion.velocity.x = 0;
            enemy.stop = true;
            if (direction.rand()) {
                motion.acceleration.y = accelerationRand.rand();
                motion.velocity.y = enemy.speed;
                updateEnemy.push_back(entity);
            } else {
                motion.acceleration.y = -accelerationRand.rand();
                motion.velocity.y = -enemy.speed;
                updateEnemy.push_back(entity);
            }
        } else {
            if (pos.y < 50 * windowScale.y) {
                motion.acceleration.y = accelerationRand.rand();
                motion.velocity.y = enemy.speed;
                updateEnemy.push_back(entity);
            } else if (pos.y > (1020 - sprite.tex.getSize().y) * windowScale.y) {
                motion.acceleration.y = -accelerationRand.rand();
                motion.velocity.y = -enemy.speed;
                updateEnemy.push_back(entity);
            }
        }
    }
    return updateEnemy;
}