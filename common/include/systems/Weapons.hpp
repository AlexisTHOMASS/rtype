/*
** EPITECH PROJECT, 2021
** rType
** File description:
** Bullets
*/

#ifndef BULLETS_HPP_
#define BULLETS_HPP_

#include "System.hpp"
#include "Coordinator.hpp"
#include <chrono>
#include <unordered_map>
#include "Weapon.hpp"
#include "BulletComp.hpp"
#include <SFML/Graphics.hpp>


class Weapons : public System {
    public:
        void init(Coordinator *coordinator);
        std::vector<Entity> update();
        void shootWith(Entity player, Entity entity);

    private:
        void __shoot(Entity entity, sf::Vector2i offset, BULLET_DAMAGE damage, char *&texture, float speed);
        void __shitShoot(Entity entity, sf::Vector2i offset);
        void __shitShootDual(Entity entity, sf::Vector2i offset);
        void __mediumShoot(Entity entity, sf::Vector2i offset);
        void __mediumShootDual(Entity entity, sf::Vector2i offset);

        void __crossMediumShitShoot(Entity entity, sf::Vector2i offset);

        void __bigAssShoot(Entity entity, sf::Vector2i offset);
        void __bigAssShootDual(Entity entity, sf::Vector2i offset);

        void __crossBigAssMediumShoot(Entity entity, sf::Vector2i offset);

    private:
        Coordinator *_coordinator;
        std::chrono::high_resolution_clock::time_point _lastShot;
        std::unordered_map<WEAPON_TYPE, void(Weapons::*)(Entity, sf::Vector2i)> _shoot;
        char *_bulletShitTexture;
        char *_bulletMediumTexture;
        char *_bulletBigAssTexture;
        std::vector<Entity> _new_bullets;
};

#endif /* !BULLETS_HPP_ */
